const float targetTime[] = {0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.1, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.19, 0.2, 0.21, 0.22, 0.23, 0.24, 0.25, 0.26, 0.27, 0.28, 0.29, 0.3, 0.31, 0.32, 0.33, 0.34, 0.35, 0.36, 0.37, 0.38, 0.39, 0.4, 0.41, 0.42, 0.43, 0.44, 0.45, 0.46, 0.47, 0.48, 0.49, 0.5, 0.51, 0.52, 0.53, 0.54, 0.55, 0.56, 0.57, 0.58, 0.59, 0.6, 0.61, 0.62, 0.63, 0.64, 0.65, 0.66, 0.67, 0.68, 0.69, 0.7, 0.71, 0.72, 0.73, 0.74, 0.75, 0.76, 0.77, 0.78, 0.79, 0.8, 0.81, 0.82, 0.83, 0.84, 0.85, 0.86, 0.87, 0.88, 0.89, 0.9, 0.91, 0.92, 0.93, 0.94, 0.95, 0.96, 0.97, 0.98, 0.99, 1, 1.01, 1.02, 1.03, 1.04, 1.05, 1.06, 1.07, 1.08, 1.09, 1.1, 1.11, 1.12, 1.13, 1.14, 1.15, 1.16, 1.17, 1.18, 1.19, 1.2, 1.21, 1.22, 1.23, 1.24, 1.25, 1.26, 1.27, 1.28, 1.29, 1.3, 1.31, 1.32, 1.33, 1.34, 1.35, 1.36, 1.37, 1.38, 1.39, 1.4, 1.41, 1.42, 1.43, 1.44, 1.45, 1.46, 1.47, 1.48, 1.49, 1.5, 1.51, 1.52, 1.53, 1.54, 1.55, 1.56, 1.57, 1.58, 1.59, 1.6, 1.61, 1.62, 1.63, 1.64, 1.65, 1.66, 1.67, 1.68, 1.69, 1.7, 1.71, 1.72, 1.73, 1.74, 1.75, 1.76, 1.77, 1.78, 1.79, 1.8, 1.81, 1.82, 1.83, 1.84, 1.85, 1.86, 1.87, 1.88, 1.89, 1.9, 1.91, 1.92, 1.93, 1.94, 1.95, 1.96, 1.97, 1.98, 1.99, 2, 2.01, 2.02, 2.03, 2.04, 2.05, 2.06, 2.07, 2.08, 2.09, 2.1, 2.11, 2.12, 2.13, 2.14, 2.15, 2.16, 2.17, 2.18, 2.19, 2.2, 2.21, 2.22, 2.23, 2.24, 2.25, 2.26, 2.27, 2.28, 2.29, 2.3, 2.31, 2.32, 2.33, 2.34, 2.35, 2.36, 2.37, 2.38, 2.39, 2.4, 2.41, 2.42, 2.43, 2.44, 2.45, 2.46, 2.47, 2.48, 2.49, 2.5, 2.51, 2.52, 2.53, 2.54, 2.55, 2.56, 2.57, 2.58, 2.59, 2.6, 2.61, 2.62, 2.63, 2.64, 2.65, 2.66, 2.67, 2.68, 2.69, 2.7, 2.71, 2.72, 2.73, 2.74, 2.75, 2.76, 2.77, 2.78, 2.79, 2.8, 2.81, 2.82, 2.83, 2.84, 2.85, 2.86, 2.87, 2.88, 2.89, 2.9, 2.91, 2.92, 2.93, 2.94, 2.95, 2.96, 2.97, 2.98, 2.99, 3, 3.01, 3.02, 3.03, 3.04, 3.05, 3.06, 3.07, 3.08, 3.09, 3.1, 3.11, 3.12, 3.13, 3.14, 3.15, 3.16, 3.17, 3.18, 3.19, 3.2, 3.21, 3.22, 3.23, 3.24, 3.25, 3.26, 3.27, 3.28, 3.29, 3.3, 3.31, 3.32, 3.33, 3.34, 3.35, 3.36, 3.37, 3.38, 3.39, 3.4, 3.41, 3.42, 3.43, 3.44, 3.45, 3.46, 3.47, 3.48, 3.49, 3.5, 3.51, 3.52, 3.53, 3.54, 3.55, 3.56, 3.57, 3.58, 3.59, 3.6, 3.61, 3.62, 3.63, 3.64, 3.65, 3.66, 3.67, 3.68, 3.69, 3.7, 3.71, 3.72, 3.73, 3.74, 3.75, 3.76, 3.77, 3.78, 3.79, 3.8, 3.81, 3.82, 3.83, 3.84, 3.85, 3.86, 3.87, 3.88, 3.89, 3.9, 3.91, 3.92, 3.93, 3.94, 3.95, 3.96, 3.97, 3.98, 3.99, 4, 4.01, 4.02, 4.03, 4.04, 4.05, 4.06, 4.07, 4.08, 4.09, 4.1, 4.11, 4.12, 4.13, 4.14, 4.15, 4.16, 4.17, 4.18, 4.19, 4.2, 4.21, 4.22, 4.23, 4.24, 4.25, 4.26, 4.27, 4.28, 4.29, 4.3, 4.31, 4.32, 4.33, 4.34, 4.35, 4.36, 4.37, 4.38, 4.39, 4.4, 4.41, 4.42, 4.43, 4.44, 4.45, 4.46, 4.47, 4.48, 4.49, 4.5, 4.51, 4.52, 4.53, 4.54, 4.55, 4.56, 4.57, 4.58, 4.59, 4.6, 4.61, 4.62, 4.63, 4.64, 4.65, 4.66, 4.67, 4.68, 4.69, 4.7, 4.71, 4.72, 4.73, 4.74, 4.75, 4.76, 4.77, 4.78, 4.79, 4.8, 4.81, 4.82, 4.83, 4.84, 4.85, 4.86, 4.87, 4.88, 4.89, 4.9, 4.91, 4.92, 4.93, 4.94, 4.95, 4.96, 4.97, 4.98, 4.99, 5, 5.01, 5.02, 5.03, 5.04, 5.05, 5.06, 5.07, 5.08, 5.09, 5.1, 5.11, 5.12, 5.13, 5.14, 5.15, 5.16, 5.17, 5.18, 5.19, 5.2, 5.21, 5.22, 5.23, 5.24, 5.25, 5.26, 5.27, 5.28, 5.29, 5.3, 5.31, 5.32, 5.33, 5.34, 5.35, 5.36, 5.37, 5.38, 5.39, 5.4, 5.41, 5.42, 5.43, 5.44, 5.45, 5.46, 5.47, 5.48, 5.49, 5.5, 5.51, 5.52, 5.53, 5.54, 5.55, 5.56, 5.57, 5.58, 5.59, 5.6, 5.61, 5.62, 5.63, 5.64, 5.65, 5.66, 5.67, 5.68, 5.69, 5.7, 5.71, 5.72, 5.73, 5.74, 5.75, 5.76, 5.77, 5.78, 5.79, 5.8, 5.81, 5.82, 5.83, 5.84, 5.85, 5.86, 5.87, 5.88, 5.89, 5.9, 5.91, 5.92, 5.93, 5.94, 5.95, 5.96, 5.97, 5.98, 5.99, 6, 6.01, 6.02, 6.03, 6.04, 6.05, 6.06, 6.07, 6.08, 6.09, 6.1, 6.11, 6.12, 6.13, 6.14, 6.15, 6.16, 6.17, 6.18, 6.19, 6.2, 6.21, 6.22, 6.23, 6.24, 6.25, 6.26};
const float targetAlt[] = {0.0056493, 0.0226545, 0.0512529, 0.0915945, 0.1436881, 0.20753, 0.283111, 0.370407, 0.4693885, 0.5800251, 0.7022822, 0.836113, 0.9814667, 1.1382914, 1.3065347, 1.486143, 1.6770622, 1.8792375, 2.092613, 2.3171325, 2.5527405, 2.7993867, 3.0570218, 3.3255957, 3.6050577, 3.8953565, 4.1964399, 4.5082553, 4.8307495, 5.1638685, 5.5075562, 5.86175, 6.2263851, 6.6013962, 6.9867173, 7.382282, 7.7880235, 8.2038743, 8.6297666, 9.0656321, 9.5114028, 9.9670133, 10.432398, 10.907493, 11.39223, 11.886545, 12.39037, 12.903639, 13.426283, 13.958236, 14.499425, 15.049768, 15.609177, 16.177566, 16.754847, 17.340933, 17.935736, 18.539168, 19.151142, 19.771568, 20.400355, 21.037394, 21.682577, 22.335791, 22.996925, 23.665868, 24.342509, 25.026721, 25.71841, 26.417465, 27.123768, 27.83719, 28.557589, 29.2848, 30.018588, 30.758608, 31.504451, 32.255671, 33.011732, 33.772056, 34.536041, 35.303043, 36.072407, 36.843482, 37.615619, 38.388211, 39.160779, 39.932892, 40.704209, 41.474496, 42.24353, 43.011161, 43.777248, 44.541653, 45.304238, 46.064859, 46.823467, 47.58001, 48.334432, 49.086681, 49.836466, 50.583431, 51.327648, 52.069127, 52.807883, 53.543928, 54.277275, 55.007936, 55.735924, 56.461251, 57.18393, 57.903972, 58.62139, 59.336196, 60.048401, 60.758017, 61.465057, 62.169532, 62.871454, 63.570833, 64.26768, 64.962008, 65.653826, 66.343147, 67.02998, 67.714337, 68.396229, 69.075666, 69.752659, 70.427218, 71.099353, 71.769076, 72.436397, 73.101324, 73.76387, 74.424042, 75.081853, 75.737311, 76.390426, 77.041208, 77.689667, 78.335812, 78.979653, 79.621198, 80.260458, 80.897442, 81.532159, 82.164618, 82.794828, 83.422798, 84.048537, 84.672054, 85.293357, 85.912457, 86.52936, 87.144076, 87.756613, 88.36698, 88.975185, 89.581237, 90.185143, 90.786912, 91.386553, 91.984073, 92.57948, 93.172782, 93.763988, 94.353105, 94.94014, 95.525103, 96.108, 96.688839, 97.267627, 97.844373, 98.419083, 98.991765, 99.562427, 100.13108, 100.69772, 101.26236, 101.82501, 102.38568, 102.94437, 103.50109, 104.05585, 104.60865, 105.1595, 105.70841, 106.25538, 106.80042, 107.34354, 107.88475, 108.42404, 108.96143, 109.49693, 110.03054, 110.56226, 111.0921, 111.62008, 112.14619, 112.67044, 113.19284, 113.71339, 114.2321, 114.74898, 115.26403, 115.77726, 116.28868, 116.79828, 117.30608, 117.81208, 118.31629, 118.81872, 119.31936, 119.81822, 120.31532, 120.81065, 121.30422, 121.79604, 122.28612, 122.77445, 123.26104, 123.7459, 124.22904, 124.71046, 125.19016, 125.66815, 126.14443, 126.61902, 127.09191, 127.56311, 128.03262, 128.50046, 128.96662, 129.43111, 129.89394, 130.355, 130.8144, 131.27215, 131.72826, 132.18273, 132.63557, 133.08678, 133.53636, 133.98432, 134.43066, 134.87539, 135.31851, 135.76004, 136.19996, 136.63829, 137.07503, 137.51019, 137.94376, 138.37576, 138.80619, 139.23505, 139.66234, 140.08808, 140.51226, 140.9349, 141.35598, 141.77553, 142.19353, 142.61, 143.02494, 143.43836, 143.85025, 144.26063, 144.66949, 145.07684, 145.48269, 145.88703, 146.28987, 146.69122, 147.09108, 147.48945, 147.88634, 148.28175, 148.67568, 149.06814, 149.45913, 149.84866, 150.23672, 150.62333, 151.00849, 151.39219, 151.77444, 152.15526, 152.53463, 152.91257, 153.28907, 153.66414, 154.03779, 154.41001, 154.78082, 155.15021, 155.51818, 155.88475, 156.24991, 156.61367, 156.97602, 157.33698, 157.69655, 158.05473, 158.41152, 158.76693, 159.12095, 159.4736, 159.82487, 160.17477, 160.52331, 160.87047, 161.21628, 161.56073, 161.90382, 162.24555, 162.58594, 162.92498, 163.26267, 163.59902, 163.93403, 164.26771, 164.60005, 164.93106, 165.26075, 165.58911, 165.91614, 166.24186, 166.56626, 166.88935, 167.21113, 167.5316, 167.85076, 168.16862, 168.48517, 168.80043, 169.1144, 169.42707, 169.73845, 170.04854, 170.35735, 170.66487, 170.97112, 171.27609, 171.57978, 171.8822, 172.18335, 172.48323, 172.78184, 173.0792, 173.37529, 173.67012, 173.9637, 174.25602, 174.5471, 174.83692, 175.1255, 175.41283, 175.69892, 175.98377, 176.26738, 176.54976, 176.8309, 177.11082, 177.3895, 177.66696, 177.94319, 178.2182, 178.49199, 178.76456, 179.03592, 179.30606, 179.57499, 179.84272, 180.10923, 180.37454, 180.63864, 180.90154, 181.16325, 181.42375, 181.68306, 181.94118, 182.1981, 182.45384, 182.70839, 182.96175, 183.21393, 183.46492, 183.71474, 183.96337, 184.21083, 184.45712, 184.70223, 184.94617, 185.18895, 185.43055, 185.67099, 185.91027, 186.14838, 186.38534, 186.62113, 186.85577, 187.08926, 187.32159, 187.55277, 187.78279, 188.01168, 188.23941, 188.466, 188.69145, 188.91575, 189.13891, 189.36094, 189.58183, 189.80158, 190.0202, 190.23769, 190.45405, 190.66928, 190.88338, 191.09636, 191.30821, 191.51894, 191.72855, 191.93703, 192.1444, 192.35066, 192.55579, 192.75982, 192.96273, 193.16453, 193.36522, 193.5648, 193.76327, 193.96064, 194.15691, 194.35207, 194.54613, 194.7391, 194.93096, 195.12172, 195.31139, 195.49997, 195.68745, 195.87384, 196.05914, 196.24335, 196.42647, 196.60851, 196.78946, 196.96932, 197.14811, 197.32581, 197.50243, 197.67797, 197.85243, 198.02581, 198.19812, 198.36935, 198.53952, 198.7086, 198.87662, 199.04357, 199.20945, 199.37426, 199.538, 199.70068, 199.86229, 200.02284, 200.18233, 200.34076, 200.49812, 200.65443, 200.80968, 200.96387, 201.11701, 201.26909, 201.42011, 201.57009, 201.71901, 201.86688, 202.01371, 202.15948, 202.3042, 202.44788, 202.59051, 202.7321, 202.87264, 203.01214, 203.1506, 203.28801, 203.42439, 203.55972, 203.69402, 203.82728, 203.9595, 204.09069, 204.22084, 204.34995, 204.47804, 204.60509, 204.7311, 204.85609, 204.98005, 205.10298, 205.22487, 205.34575, 205.46559, 205.58441, 205.7022, 205.81897, 205.93471, 206.04944, 206.16313, 206.27581, 206.38747, 206.4981, 206.60772, 206.71632, 206.8239, 206.93046, 207.036, 207.14053, 207.24405, 207.34655, 207.44803, 207.54851, 207.64796, 207.74641, 207.84385, 207.94027, 208.03569, 208.13009, 208.22349, 208.31588, 208.40726, 208.49763, 208.587, 208.67536, 208.76271, 208.84906, 208.93441, 209.01875, 209.10209, 209.18442, 209.26576, 209.34609, 209.42542, 209.50375, 209.58108, 209.65741, 209.73274, 209.80707, 209.8804, 209.95274, 210.02408, 210.09442, 210.16376, 210.23211, 210.29947, 210.36583, 210.43119, 210.49556, 210.55893, 210.62131, 210.6827, 210.7431, 210.8025, 210.86091, 210.91833, 210.97476, 211.0302, 211.08465, 211.1381, 211.19057, 211.24205, 211.29253, 211.34203, 211.39054, 211.43807, 211.4846, 211.53015, 211.57471, 211.61828, 211.66086, 211.70246, 211.74307, 211.7827, 211.82134, 211.85899, 211.89566, 211.93135, 211.96604, 211.99976, 212.03249, 212.06423, 212.09499, 212.12477, 212.15357, 212.18138, 212.2082, 212.23405, 212.25891, 212.28278, 212.30568, 212.32759, 212.34852, 212.36847, 212.38743, 212.40541, 212.42241, 212.43843, 212.45347, 212.46752, 212.4806, 212.49269, 212.5038, 212.51393, 212.52307, 212.53124, 212.53842, 212.54462, 212.54985, 212.55408, 212.55738, 212.55969, 212.56101};
