const SERIAL_PORT: &str = "/dev/cu.usbmodem14201";
const OUTPUT_PATH: &str = "flight.csv";
use robust_arduino_serial::*;
use serde::Serialize;
use serial::{prelude::*, SystemPort};
use std::process::Output;
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
    println!("Connecting...");
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
            println!("Connected!");
            break;
        }
    }

    // Begin transfer
    serial_send(&mut port);

    // Get frame count
    let frame_count = read_i32(&mut port).unwrap();
    println!("Frames available: {}", frame_count);
    serial_send(&mut port);

    // Get frames
    let mut frames = Vec::new();
    for i in 0..frame_count {
        // Read frame
        let mut buff: [u8; FRAME_SIZE] = [0; FRAME_SIZE];
        for j in 0..FRAME_SIZE {
            let mut read_buffer = [0u8; 1];
            port.read_exact(&mut read_buffer).unwrap();
            buff[j] = read_buffer[0];
        }

        // Move to frame
        let mut frame: DataFrame = unsafe { mem::zeroed() };
        unsafe {
            let config_slice =
                slice::from_raw_parts_mut(&mut frame as *mut _ as *mut u8, FRAME_SIZE);
            // `read_exact()` comes from `Read` impl for `&[u8]`
            (&buff[0..buff.len()]).read_exact(config_slice).unwrap();
        }

        // Save frame
        frames.push(frame);
        serial_send(&mut port);
        println!(
            "Reading frames... {}%",
            (i as f32 / frame_count as f32) * 100.0
        );
    }

    // Write to CSV
    println!("Writing frames...");
    let mut writer = csv::Writer::from_path(OUTPUT_PATH).unwrap();
    for frame in frames {
        writer.serialize(frame).unwrap();
    }
    writer.flush().unwrap();
    println!("Wrote frames!");

    // Close
    serial_send(&mut port);
}
