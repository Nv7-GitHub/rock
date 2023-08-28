const SERIAL_PORT: &str = "/dev/cu.usbmodem14201";
const OUTPUT_PATH: &str = "flight.csv";
use console::style;
use indicatif::ProgressBar;
use robust_arduino_serial::*;
use serde::Serialize;
use serial::{prelude::*, SystemPort};
use std::io::Write;
use std::slice;
use std::time::Duration;
use std::{io::Read, mem};

fn serial_send(port: &mut SystemPort) {
    write_i8(port, 1).unwrap();
}

#[repr(C, packed)]
#[derive(Debug, Copy, Clone, Serialize)]
struct DataFrame {
    time: u32,
    state: i32,
    accel: f32,
    vel: f32,
    alt: f32,
    roll: f32,
    s1: i32,
    s2: i32,
    s3: i32,
    ax: f32,
    ay: f32,
    az: f32,
    gx: f32,
    gy: f32,
    gz: f32,
    baro: f32,
    temp: f32,
}
const FRAME_SIZE: usize = mem::size_of::<DataFrame>();

fn main() {
    println!("{} Connecting to ROCK...", style("[1/6]").bold().dim());

    let mut port = serial::open(&SERIAL_PORT).unwrap();
    port.configure(&serial::PortSettings {
        baud_rate: serial::Baud9600,
        char_size: serial::Bits8,
        parity: serial::ParityNone,
        stop_bits: serial::Stop1,
        flow_control: serial::FlowNone,
    })
    .unwrap();
    port.set_timeout(Duration::from_secs(30)).unwrap();

    // Wait for beginning byte
    loop {
        let v = read_i8(&mut port).unwrap();
        if v == 1 {
            break; // Connected!
        }
    }

    // Begin transfer
    serial_send(&mut port);

    // Get frame count
    let sector_count = read_i32(&mut port).unwrap();
    println!(
        "{} Sectors available: {}",
        style("[2/6]").bold().dim(),
        sector_count
    );
    serial_send(&mut port);

    // Get sectors
    println!("{} Reading sectors...", style("[3/6]").bold().dim());
    let pb = ProgressBar::new(sector_count as u64);
    let mut data = Vec::new();
    for _ in 0..sector_count {
        // Read sector
        let mut buff: [u8; 4096] = [0; 4096];
        for j in 0..4096 {
            let mut read_buffer = [0u8; 1];
            port.read_exact(&mut read_buffer).unwrap();
            buff[j] = read_buffer[0];
        }
        data.append(&mut buff.to_vec());

        // Update
        serial_send(&mut port);
        pb.inc(1);
    }
    pb.finish_and_clear();

    // Process frames
    let mut frames = Vec::new();
    for i in 0..(data.len() / FRAME_SIZE) {
        let mut has_frame = false;
        for j in 0..FRAME_SIZE {
            if data[FRAME_SIZE * i + j] != 255 {
                has_frame = true;
                break;
            }
        }
        if !has_frame {
            break;
        }

        // Move to frame
        let mut frame: DataFrame = unsafe { mem::zeroed() };
        unsafe {
            let config_slice =
                slice::from_raw_parts_mut(&mut frame as *mut _ as *mut u8, FRAME_SIZE);
            // `read_exact()` comes from `Read` impl for `&[u8]`
            (&data[i * FRAME_SIZE..(i + 1) * FRAME_SIZE])
                .read_exact(config_slice)
                .unwrap();
        }

        // Save frame
        frames.push(frame);
    }

    // Write to CSV
    println!("{} Writing frames...", style("[4/6]").bold().dim());
    let mut writer = csv::Writer::from_path(OUTPUT_PATH).unwrap();
    for frame in frames {
        writer.serialize(frame).unwrap();
    }
    writer.flush().unwrap();

    // OK the transfer
    /*serial_send(&mut port);
    port.flush().unwrap();
    println!("{} Erasing flash chip...", style("[5/6]").bold().dim());

    // Wait for erase
    loop {
        let v = read_i8(&mut port).unwrap();
        if v == 1 {
            break; // Connected!
        }
    }
    println!("{} Done!", style("[6/6]").bold().dim());*/
}
