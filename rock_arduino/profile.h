const float targetTime[] = {0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.1, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.19, 0.2, 0.21, 0.22, 0.23, 0.24, 0.25, 0.26, 0.27, 0.28, 0.29, 0.3, 0.31, 0.32, 0.33, 0.34, 0.35, 0.36, 0.37, 0.38, 0.39, 0.4, 0.41, 0.42, 0.43, 0.44, 0.45, 0.46, 0.47, 0.48, 0.49, 0.5, 0.51, 0.52, 0.53, 0.54, 0.55, 0.56, 0.57, 0.58, 0.59, 0.6, 0.61, 0.62, 0.63, 0.64, 0.65, 0.66, 0.67, 0.68, 0.69, 0.7, 0.71, 0.72, 0.73, 0.74, 0.75, 0.76, 0.77, 0.78, 0.79, 0.8, 0.81, 0.82, 0.83, 0.84, 0.85, 0.86, 0.87, 0.88, 0.89, 0.9, 0.91, 0.92, 0.93, 0.94, 0.95, 0.96, 0.97, 0.98, 0.99, 1, 1.01, 1.02, 1.03, 1.04, 1.05, 1.06, 1.07, 1.08, 1.09, 1.1, 1.11, 1.12, 1.13, 1.14, 1.15, 1.16, 1.17, 1.18, 1.19, 1.2, 1.21, 1.22, 1.23, 1.24, 1.25, 1.26, 1.27, 1.28, 1.29, 1.3, 1.31, 1.32, 1.33, 1.34, 1.35, 1.36, 1.37, 1.38, 1.39, 1.4, 1.41, 1.42, 1.43, 1.44, 1.45, 1.46, 1.47, 1.48, 1.49, 1.5, 1.51, 1.52, 1.53, 1.54, 1.55, 1.56, 1.57, 1.58, 1.59, 1.6, 1.61, 1.62, 1.63, 1.64, 1.65, 1.66, 1.67, 1.68, 1.69, 1.7, 1.71, 1.72, 1.73, 1.74, 1.75, 1.76, 1.77, 1.78, 1.79, 1.8, 1.81, 1.82, 1.83, 1.84, 1.85, 1.86, 1.87, 1.88, 1.89, 1.9, 1.91, 1.92, 1.93, 1.94, 1.95, 1.96, 1.97, 1.98, 1.99, 2, 2.01, 2.02, 2.03, 2.04, 2.05, 2.06, 2.07, 2.08, 2.09, 2.1, 2.11, 2.12, 2.13, 2.14, 2.15, 2.16, 2.17, 2.18, 2.19, 2.2, 2.21, 2.22, 2.23, 2.24, 2.25, 2.26, 2.27, 2.28, 2.29, 2.3, 2.31, 2.32, 2.33, 2.34, 2.35, 2.36, 2.37, 2.38, 2.39, 2.4, 2.41, 2.42, 2.43, 2.44, 2.45, 2.46, 2.47, 2.48, 2.49, 2.5, 2.51, 2.52, 2.53, 2.54, 2.55, 2.56, 2.57, 2.58, 2.59, 2.6, 2.61, 2.62, 2.63, 2.64, 2.65, 2.66, 2.67, 2.68, 2.69, 2.7, 2.71, 2.72, 2.73, 2.74, 2.75, 2.76, 2.77, 2.78, 2.79, 2.8, 2.81, 2.82, 2.83, 2.84, 2.85, 2.86, 2.87, 2.88, 2.89, 2.9, 2.91, 2.92, 2.93, 2.94, 2.95, 2.96, 2.97, 2.98, 2.99, 3, 3.01, 3.02, 3.03, 3.04, 3.05, 3.06, 3.07, 3.08, 3.09, 3.1, 3.11, 3.12, 3.13, 3.14, 3.15, 3.16, 3.17, 3.18, 3.19, 3.2, 3.21, 3.22, 3.23, 3.24, 3.25, 3.26, 3.27, 3.28, 3.29, 3.3, 3.31, 3.32, 3.33, 3.34, 3.35, 3.36, 3.37, 3.38, 3.39, 3.4, 3.41, 3.42, 3.43, 3.44, 3.45, 3.46, 3.47, 3.48, 3.49, 3.5, 3.51, 3.52, 3.53, 3.54, 3.55, 3.56, 3.57, 3.58, 3.59, 3.6, 3.61, 3.62, 3.63, 3.64, 3.65, 3.66, 3.67, 3.68, 3.69, 3.7, 3.71, 3.72, 3.73, 3.74, 3.75, 3.76, 3.77, 3.78, 3.79, 3.8, 3.81, 3.82, 3.83, 3.84, 3.85, 3.86, 3.87, 3.88, 3.89, 3.9, 3.91, 3.92, 3.93, 3.94, 3.95, 3.96, 3.97, 3.98, 3.99, 4, 4.01, 4.02, 4.03, 4.04, 4.05, 4.06, 4.07, 4.08, 4.09, 4.1, 4.11, 4.12, 4.13, 4.14, 4.15, 4.16, 4.17, 4.18, 4.19, 4.2, 4.21, 4.22, 4.23, 4.24, 4.25, 4.26, 4.27, 4.28, 4.29, 4.3, 4.31, 4.32, 4.33, 4.34, 4.35, 4.36, 4.37, 4.38, 4.39, 4.4, 4.41, 4.42, 4.43, 4.44, 4.45, 4.46, 4.47, 4.48, 4.49, 4.5, 4.51, 4.52, 4.53, 4.54, 4.55, 4.56, 4.57, 4.58, 4.59, 4.6, 4.61, 4.62, 4.63, 4.64, 4.65, 4.66, 4.67, 4.68, 4.69, 4.7, 4.71, 4.72, 4.73, 4.74, 4.75, 4.76, 4.77, 4.78, 4.79, 4.8, 4.81, 4.82, 4.83, 4.84, 4.85, 4.86, 4.87, 4.88, 4.89, 4.9, 4.91, 4.92, 4.93, 4.94, 4.95, 4.96, 4.97, 4.98, 4.99, 5, 5.01, 5.02, 5.03, 5.04, 5.05, 5.06, 5.07, 5.08, 5.09, 5.1, 5.11, 5.12, 5.13, 5.14, 5.15, 5.16, 5.17, 5.18, 5.19, 5.2, 5.21, 5.22, 5.23, 5.24, 5.25, 5.26, 5.27, 5.28, 5.29, 5.3, 5.31, 5.32, 5.33, 5.34, 5.35, 5.36, 5.37, 5.38, 5.39, 5.4, 5.41, 5.42, 5.43, 5.44, 5.45, 5.46, 5.47, 5.48, 5.49, 5.5, 5.51, 5.52, 5.53, 5.54, 5.55, 5.56, 5.57, 5.58, 5.59, 5.6, 5.61, 5.62, 5.63, 5.64, 5.65, 5.66, 5.67, 5.68, 5.69, 5.7, 5.71, 5.72, 5.73, 5.74, 5.75, 5.76, 5.77, 5.78, 5.79, 5.8, 5.81, 5.82, 5.83, 5.84, 5.85, 5.86, 5.87, 5.88, 5.89, 5.9, 5.91, 5.92, 5.93, 5.94, 5.95, 5.96, 5.97, 5.98, 5.99, 6, 6.01, 6.02, 6.03, 6.04, 6.05, 6.06, 6.07, 6.08, 6.09, 6.1, 6.11, 6.12, 6.13, 6.14, 6.15, 6.16, 6.17, 6.18, 6.19, 6.2, 6.21, 6.22, 6.23, 6.24, 6.25, 6.26, 6.27, 6.28, 6.29, 6.3, 6.31, 6.32, 6.33, 6.34, 6.35, 6.36, 6.37, 6.38, 6.39, 6.4, 6.41, 6.42, 6.43, 6.44, 6.45, 6.46, 6.47, 6.48, 6.49, 6.5, 6.51, 6.52, 6.53, 6.54, 6.55, 6.56, 6.57, 6.58, 6.59, 6.6, 6.61, 6.62, 6.63, 6.64, 6.65, 6.66, 6.67, 6.68, 6.69, 6.7, 6.71, 6.72};
const float targetAlt[] = {0.0054376, 0.0218059, 0.0493347, 0.0881697, 0.1383208, 0.199786, 0.2725589, 0.3566184, 0.4519391, 0.5584951, 0.6762515, 0.805175, 0.9452181, 1.0963356, 1.2584818, 1.4316107, 1.6156758, 1.8106302, 2.0164265, 2.2330172, 2.4603557, 2.6984009, 2.947113, 3.2064516, 3.4763759, 3.756845, 4.0478175, 4.3492516, 4.6611052, 4.9833361, 5.3158997, 5.658746, 6.0118225, 6.375077, 6.7484564, 7.1319078, 7.5253776, 7.9288123, 8.3421579, 8.7653601, 9.1983654, 9.6411225, 10.093581, 10.55569, 11.027398, 11.508654, 11.999407, 12.499604, 13.009194, 13.528124, 14.056339, 14.593771, 15.14035, 15.696006, 16.260667, 16.834262, 17.416721, 18.007972, 18.607944, 19.216565, 19.833759, 20.459436, 21.093502, 21.735865, 22.386429, 23.045101, 23.711788, 24.386393, 25.068807, 25.758953, 26.456729, 27.162024, 27.874713, 28.594648, 29.321614, 30.055289, 30.795289, 31.541192, 32.292489, 33.04863, 33.80904, 34.573104, 35.340191, 36.109676, 36.880933, 37.653376, 38.426541, 39.200007, 39.973446, 40.746623, 41.519325, 42.291396, 43.062698, 43.833091, 44.602436, 45.370595, 46.137509, 46.90312, 47.66737, 48.430199, 49.191314, 49.950375, 50.70744, 51.462514, 52.215603, 52.966711, 53.715844, 54.463008, 55.208207, 55.951446, 56.692731, 57.432067, 58.169459, 58.904912, 59.63843, 60.37002, 61.099686, 61.827432, 62.553265, 63.277188, 63.999207, 64.719326, 65.437551, 66.153885, 66.868335, 67.580904, 68.291598, 69.000421, 69.707377, 70.412472, 71.11571, 71.817095, 72.516633, 73.214328, 73.910184, 74.604206, 75.296398, 75.986765, 76.675311, 77.362041, 78.046959, 78.73007, 79.411377, 80.090886, 80.7686, 81.444523, 82.118661, 82.791017, 83.461596, 84.130401, 84.797438, 85.462709, 86.12622, 86.787974, 87.447975, 88.106228, 88.762736, 89.417504, 90.070536, 90.721836, 91.371407, 92.019254, 92.66538, 93.30979, 93.952487, 94.593476, 95.232759, 95.870342, 96.506228, 97.14042, 97.772923, 98.403739, 99.032874, 99.660331, 100.28611, 100.91022, 101.53267, 102.15345, 102.77257, 103.39003, 104.00585, 104.62001, 105.23253, 105.8434, 106.45253, 107.06002, 107.66589, 108.27013, 108.87274, 109.47374, 110.07311, 110.67088, 111.26703, 111.86158, 112.45453, 113.04587, 113.63562, 114.22378, 114.81035, 115.39533, 115.97873, 116.56055, 117.14079, 117.71946, 118.29655, 118.87209, 119.44605, 120.01846, 120.58931, 121.1586, 121.72635, 122.29254, 122.85719, 123.4203, 123.98187, 124.5419, 125.1004, 125.65738, 126.21282, 126.76674, 127.31914, 127.87002, 128.41939, 128.96724, 129.51359, 130.05843, 130.60176, 131.1436, 131.68394, 132.22278, 132.76013, 133.296, 133.83037, 134.36327, 134.89468, 135.42461, 135.95307, 136.48006, 137.00558, 137.52963, 138.05221, 138.57334, 139.09301, 139.61122, 140.12797, 140.64328, 141.15714, 141.66955, 142.18052, 142.69005, 143.19814, 143.70479, 144.21002, 144.71381, 145.21617, 145.71712, 146.21663, 146.71473, 147.21141, 147.70668, 148.20053, 148.69297, 149.18401, 149.67364, 150.16187, 150.64869, 151.13412, 151.61816, 152.1008, 152.58205, 153.06191, 153.54038, 154.01748, 154.49319, 154.96752, 155.44047, 155.91205, 156.38226, 156.8511, 157.31856, 157.78467, 158.24941, 158.71279, 159.17481, 159.63548, 160.09479, 160.55275, 161.00935, 161.46461, 161.91853, 162.3711, 162.82233, 163.27222, 163.72078, 164.168, 164.61388, 165.05844, 165.50167, 165.94357, 166.38414, 166.8234, 167.26133, 167.69794, 168.13324, 168.56723, 168.9999, 169.43126, 169.86131, 170.29006, 170.7175, 171.14364, 171.56848, 171.99203, 172.41427, 172.83522, 173.25488, 173.67325, 174.09032, 174.50611, 174.92062, 175.33384, 175.74578, 176.15645, 176.56583, 176.97394, 177.38077, 177.78634, 178.19063, 178.59365, 178.99541, 179.3959, 179.79513, 180.1931, 180.58981, 180.98526, 181.37945, 181.77239, 182.16408, 182.55452, 182.9437, 183.33164, 183.71834, 184.10379, 184.488, 184.87097, 185.25269, 185.63319, 186.01244, 186.39046, 186.76725, 187.14281, 187.51714, 187.89025, 188.26212, 188.63278, 189.00221, 189.37041, 189.7374, 190.10318, 190.46773, 190.83107, 191.1932, 191.55412, 191.91382, 192.27232, 192.62961, 192.9857, 193.34058, 193.69426, 194.04673, 194.39801, 194.74809, 195.09698, 195.44467, 195.79116, 196.13646, 196.48058, 196.8235, 197.16524, 197.50579, 197.84515, 198.18333, 198.52033, 198.85615, 199.19079, 199.52425, 199.85653, 200.18764, 200.51758, 200.84634, 201.17394, 201.50036, 201.82561, 202.1497, 202.47262, 202.79438, 203.11497, 203.43441, 203.75266, 204.06979, 204.38538, 204.69934, 205.01172, 205.32252, 205.63175, 205.93941, 206.2455, 206.55004, 206.85303, 207.15448, 207.45438, 207.75275, 208.0496, 208.34492, 208.63873, 208.93102, 209.22181, 209.5111, 209.7989, 210.0852, 210.37002, 210.65337, 210.93524, 211.21564, 211.49457, 211.77205, 212.04807, 212.32265, 212.59578, 212.86747, 213.13773, 213.40656, 213.67397, 213.93995, 214.20452, 214.46768, 214.72943, 214.98978, 215.24874, 215.5063, 215.76247, 216.01726, 216.27068, 216.52271, 216.77338, 217.02267, 217.27061, 217.51719, 217.76241, 218.00628, 218.24881, 218.49, 218.72984, 218.96836, 219.20554, 219.4414, 219.67593, 219.90915, 220.14105, 220.37164, 220.60093, 220.82891, 221.05559, 221.28097, 221.50498, 221.72769, 221.94913, 222.16928, 222.38815, 222.60575, 222.82208, 223.03714, 223.25093, 223.46347, 223.67475, 223.88477, 224.09354, 224.30106, 224.50734, 224.71238, 224.91618, 225.11874, 225.32007, 225.52018, 225.71905, 225.91671, 226.11314, 226.30835, 226.50235, 226.69514, 226.88672, 227.0771, 227.26627, 227.45424, 227.64102, 227.8266, 228.01099, 228.19419, 228.3762, 228.55703, 228.73668, 228.91515, 229.09244, 229.26856, 229.44351, 229.61729, 229.78991, 229.96136, 230.13165, 230.30078, 230.46876, 230.63558, 230.80125, 230.96578, 231.12915, 231.29138, 231.45247, 231.61243, 231.77124, 231.92892, 232.08546, 232.24087, 232.39516, 232.54832, 232.70035, 232.85126, 233.00105, 233.14973, 233.29729, 233.44373, 233.58906, 233.73328, 233.87639, 234.0184, 234.1593, 234.2991, 234.4378, 234.5754, 234.71191, 234.84732, 234.98163, 235.11486, 235.247, 235.37804, 235.50801, 235.63688, 235.76468, 235.8914, 236.01703, 236.14159, 236.26507, 236.38748, 236.50882, 236.62909, 236.74828, 236.86641, 236.98347, 237.09947, 237.21441, 237.32828, 237.44109, 237.55285, 237.66354, 237.77319, 237.88177, 237.98931, 238.09579, 238.20123, 238.30561, 238.40895, 238.51124, 238.61248, 238.71269, 238.81185, 238.90997, 239.00705, 239.10309, 239.19809, 239.29206, 239.38499, 239.4769, 239.56776, 239.6576, 239.74641, 239.83418, 239.92093, 240.00666, 240.09135, 240.17503, 240.25768, 240.3393, 240.41991, 240.49949, 240.57806, 240.6556, 240.73213, 240.80765, 240.88214, 240.95563, 241.0281, 241.09955, 241.17, 241.23943, 241.30785, 241.37526, 241.44167, 241.50707, 241.57146, 241.63484, 241.69722, 241.75859, 241.81897, 241.87833, 241.9367, 241.99406, 242.05043, 242.10579, 242.16015, 242.21352, 242.26588, 242.31725, 242.36762, 242.417, 242.46538, 242.51276, 242.55915, 242.60455, 242.64895, 242.69236, 242.73478, 242.77621, 242.81664, 242.85609, 242.89454, 242.93201, 242.96848, 243.00397, 243.03846, 243.07197, 243.10449, 243.13603, 243.16658, 243.19614, 243.22471, 243.2523, 243.2789, 243.30452, 243.32916, 243.3528, 243.37547, 243.39715, 243.41785, 243.43756, 243.45629, 243.47404, 243.4908, 243.50658, 243.52138, 243.5352, 243.54803, 243.55989, 243.57076, 243.58065, 243.58955, 243.59748, 243.60442, 243.61039, 243.61537, 243.61936, 243.62238, 243.62444, 243.62552};
