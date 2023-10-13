#include "classification.h"

enum State currentState = SEARCHING_FOR_PEAK;
enum State nextState = SEARCHING_FOR_PEAK;

int bufferIndex = -1;
int startIndex = 0;
int stopIndex = 0;
int missingSamples = WINDOW_SIZE / 2;
bool canClassify = true;

Sample circularBuffer[BUFFER_SIZE] = {};
Movement dataset[DATASET_SIZE] = {
                                  // STRAIGHT JUMP
                                  {
                                   .movFeatures = {
                                                   0.13096, 0.67755, 0.25932, -0.01477, -0.94688, -0.07153, 0.06553, 3.19319
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.12684, 0.67095, 0.25992, -0.03802, -0.94111, -0.16256, 0.03570, 2.92291
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.10710, 0.65663, 0.26903, -0.05073, -0.94538, -0.13699, 0.03369, 2.71229
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.11097, 0.69209, 0.24715, -0.03716, -0.92638, -0.13084, 0.07674, 2.92951
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.14183, 0.66301, 0.26597, -0.06643, -0.93055, -0.14721, 0.05522, 2.94972
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.14603, 0.64563, 0.34607, -0.10216, -0.93152, -0.20775, 0.04578, 2.75426
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.15681, 0.69002, 0.33181, -0.05124, -0.93822, -0.15042, 0.06901, 2.72128
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.14679, 0.65156, 0.32211, -0.02465, -0.93833, -0.22427, 0.06725, 2.74710
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.12187, 0.60339, 0.25770, -0.00486, -0.95293, -0.12028, 0.02874, 2.73332
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.16352, 0.64148, 0.35385, -0.06130, -0.93608, -0.15447, 0.05962, 3.13621
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  // SIT DOWN ON A CHAIR
                                  {
                                   .movFeatures = {
                                                   0.04717, 0.15339, 0.36511, 0.12488, -0.92144, 0.09980, 0.50118, 1.90923
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.08042, 0.16426, 0.38496, 0.12881, -0.89818, 0.16317, 0.54742, 1.97134
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.09458, 0.10375, 0.44259, 0.12441, -0.88361, 0.09129, 0.69188, 1.72653
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.09162, 0.09307, 0.39178, 0.08732, -0.90860, 0.05688, 0.62273, 1.44349
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.14027, 0.10231, 0.47564, 0.19299, -0.84559, 0.07532, 0.62567, 1.25260
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.08292, 0.10333, 0.38398, 0.11490, -0.91298, 0.00877, 0.62474, 1.29468
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.08646, 0.11563, 0.42709, 0.12157, -0.88517, -0.03926, 0.76708, 1.39677
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.09850, 0.11116, 0.41389, 0.18207, -0.88352, -0.04853, 0.67703, 1.48295
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.06911, 0.08981, 0.41130, 0.16600, -0.89340, -0.01291, 0.63727, 1.31507
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.13579, 0.11870, 0.41674, 0.13146, -0.88611, -0.10373, 0.58537, 1.53360
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  // STAND UP FROM A CHAIR
                                  {
                                   .movFeatures = {
                                                   0.10989, 0.10427, 0.31355, 0.11438, -0.92638, -0.12897, 0.64311, 1.34394
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.07984, 0.10535, 0.37909, 0.09126, -0.90360, -0.12997, 0.73546, 1.32794
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.09394, 0.09165, 0.27502, 0.11267, -0.94529, -0.07969, 0.65897, 1.34637
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.05872, 0.08733, 0.37348, 0.09909, -0.91939, 0.01235, 0.65955, 1.45487
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.06100, 0.07396, 0.36709, 0.13813, -0.91557, -0.03588, 0.69996, 1.24270
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.03970, 0.07255, 0.32360, 0.14240, -0.93289, -0.00698, 0.75358, 1.41862
                                  },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.05809, 0.10075, 0.42049, 0.09360, -0.89490, -0.04071, 0.58672, 1.26862
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.07628, 0.08654, 0.44521, 0.09779, -0.88204, 0.00469, 0.72863, 1.19833
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.06729, 0.07056, 0.35111, 0.10557, -0.92502, -0.00973, 0.77158, 1.30483
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.08593, 0.09112, 0.39124, 0.10667, -0.90540, -0.06610, 0.73315, 1.37555
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  // LAY DOWN ON BED
                                  {
                                   .movFeatures = {
                                                   0.15064, 0.39481, 0.48380, 0.22520, -0.51377, 0.57778, 0.71550, 1.57919
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.20274, 0.42191, 0.48411, 0.21469, -0.51099, 0.55154, 0.72952, 1.59656
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.17037, 0.41912, 0.55104, 0.19868, -0.55156, 0.44943, 0.60586, 1.43651
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.17676, 0.42922, 0.46311, 0.20229, -0.56730, 0.51236, 0.72247, 1.58692
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.16060, 0.38644, 0.66320, 0.19055, -0.49659, 0.39465, 0.66988, 1.74544
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.20820, 0.36889, 0.65913, 0.20172, -0.53430, 0.32839, 0.68604, 1.49818
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.24887, 0.38623, 0.61392, 0.25259, -0.58192, 0.24680, 0.67889, 1.59952
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.25780, 0.38124, 0.63440, 0.20436, -0.52207, 0.34953, 0.69300, 1.48811
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.27219, 0.35321, 0.60833, 0.21826, -0.64266, 0.13498, 0.65422, 1.76150
                                  },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.24090, 0.37460, 0.61308, 0.22753, -0.55206, 0.33246, 0.76997, 1.36806
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  // GET UP FROM BED
                                  {
                                   .movFeatures = {
                                                   0.20236, 0.37974, 0.65473, 0.10370, -0.54919, 0.33174, 0.75660, 1.27529
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.22061, 0.35508, 0.64172, 0.16243, -0.60612, 0.23752, 0.72096, 1.31283
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.16244, 0.34878, 0.63480, 0.11953, -0.58151, 0.36273, 0.69433, 1.26796
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.16255, 0.36243, 0.65474, 0.14393, -0.54765, 0.35975, 0.69009, 1.26858
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.21050, 0.35126, 0.59313, 0.16685, -0.58798, 0.38227, 0.64151, 1.32430
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.17741, 0.37286, 0.54907, 0.13031, -0.68345, 0.27736, 0.55713, 1.28584
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.18922, 0.37168, 0.64714, 0.12796, -0.52248, 0.39910, 0.71285, 1.36416
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.22453, 0.38048, 0.62919, 0.12237, -0.60607, 0.27767, 0.54605, 1.60926
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.14792, 0.42329, 0.57474, 0.13061, -0.52690, 0.45838, 0.62857, 1.23299
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.15272, 0.37425, 0.56010, 0.12865, -0.65551, 0.32999, 0.64357, 1.46829
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  // RUN
                                  {
                                   .movFeatures = {
                                                   0.10955, 0.69856, 0.14317, -0.05021, -0.98914, -0.05906, 0.01625, 2.50077
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.15412, 0.75055, 0.17414, -0.06273, -0.99517, -0.02805, 0.05689, 2.53820
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.12709, 0.66939, 0.15248, -0.00929, -0.99743, 0.02534, 0.02369, 2.31492
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.10537, 0.58123, 0.12890, -0.04226, -0.98620, 0.03951, 0.02539, 2.14700
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.11964, 0.69434, 0.15678, 0.04390, -0.99639, -0.02027, 0.04007, 2.41049
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.10515, 0.62865, 0.14741, 0.02044, -0.99349, -0.01777, 0.01861, 2.25861
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.11940, 0.73225, 0.14195, 0.03506, -0.97318, -0.07667, 0.03294, 2.38079
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.12278, 0.63527, 0.16775, -0.00451, -0.97397, -0.07312, 0.01878, 2.29141
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.13003, 0.63126, 0.13936, -0.06493, -0.98922, -0.08513, 0.04859, 2.23180
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.09713, 0.59053, 0.12695, -0.01387, -0.98644, -0.05596, 0.02067, 2.24710
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  // BEND DOWN TO PICK UP
                                  {
                                   .movFeatures = {
                                                   0.14815, 0.33620, 0.46660, 0.08228, -0.68057, -0.42448, 0.64520, 1.39670
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.11337, 0.30921, 0.44255, 0.09406, -0.70037, -0.45599, 0.64364, 1.54326
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.11624, 0.29124, 0.42343, 0.04004, -0.69792, -0.48539, 0.64216, 1.43707
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.08510, 0.22488, 0.41153, 0.03326, -0.76729, -0.42811, 0.69536, 1.30712
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.10463, 0.15380, 0.38825, 0.13949, -0.84450, -0.31510, 0.67654, 1.43271
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.11872, 0.21075, 0.40626, 0.06473, -0.75771, -0.45121, 0.66508, 1.51193
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.07698, 0.17772, 0.36584, 0.10768, -0.84013, -0.36677, 0.73248, 1.81116
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.06924, 0.15613, 0.33298, 0.07258, -0.81730, -0.42674, 0.67507, 1.32896
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.09806, 0.18060, 0.36690, 0.11249, -0.79710, -0.41484, 0.68944, 1.33596
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.08743, 0.14034, 0.31056, 0.18055, -0.83711, -0.39098, 0.63773, 1.38161
                                   },
                                   .movClass = ADL,
                                   .toSkip = false
                                  },
                                  // FALL BACK
                                  {
                                   .movFeatures = {
                                                   0.17359, 0.48365, 0.64362, 0.14676, -0.35975, 0.65749, 0.09535, 3.08770
                                   },
                                   .movClass = FALL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.19873, 0.49975, 0.64535, 0.10502, -0.38802, 0.62262, 0.07282, 3.05303
                                   },
                                   .movClass = FALL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.13166, 0.52324, 0.66561, 0.07882, -0.38774, 0.58045, 0.10370, 2.98279
                                   },
                                   .movClass = FALL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.15686, 0.56837, 0.67847, 0.09029, -0.54378, 0.38677, 0.05162, 3.08113
                                   },
                                   .movClass = FALL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.14325, 0.54050, 0.68340, 0.07458, -0.50129, 0.43260, 0.09638, 2.74672
                                   },
                                   .movClass = FALL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.18310, 0.57128, 0.66201, 0.02216, -0.49463, 0.49144, 0.06581, 3.05232
                                   },
                                   .movClass = FALL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.16605, 0.54148, 0.63816, 0.03525, -0.46482, 0.56112, 0.10616, 2.97929
                                   },
                                   .movClass = FALL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.19301, 0.55214, 0.65070, 0.07006, -0.48955, 0.54601, 0.05250, 3.39430
                                   },
                                   .movClass = FALL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.13669, 0.56211, 0.63556, 0.05780, -0.45366, 0.56528, 0.01653, 2.92212                                   },
                                   .movClass = FALL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.14941, 0.54458, 0.64019, 0.12094, -0.43864, 0.54486, 0.23528, 3.10358                                   },
                                   .movClass = FALL,
                                   .toSkip = false
                                  },
                                  // FALL LEFT SIDE
                                  {
                                   .movFeatures = {
                                                   0.57977, 0.57608, 0.26503, 0.65796, -0.30460, -0.03134, 0.05502, 3.46933
                                   },
                                   .movClass = FALL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.50981, 0.50777, 0.34259, 0.51503, -0.43096, -0.29700, 0.03627, 3.40540
                                   },
                                   .movClass = FALL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.45695, 0.54986, 0.33828, 0.54089, -0.22466, -0.48824, 0.04402, 3.57748
                                   },
                                   .movClass = FALL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.55331, 0.36733, 0.22395, 0.66049, -0.56756, 0.17330, 0.08062, 3.10374
                                   },
                                   .movClass = FALL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.46165, 0.41682, 0.54729, 0.57819, -0.48143, -0.08335, 0.14279, 3.24208
                                   },
                                   .movClass = FALL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.54737, 0.43311, 0.45551, 0.49338, -0.58784, -0.18675, 0.11862, 3.46273
                                   },
                                   .movClass = FALL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.54355, 0.42382, 0.51944, 0.54267, -0.52033, -0.07916, 0.04561, 3.43896
                                   },
                                   .movClass = FALL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.54203, 0.41778, 0.33671, 0.53849, -0.54775, -0.21865, 0.18767, 2.67438
                                   },
                                   .movClass = FALL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.56046, 0.39983, 0.32448, 0.64077, -0.52364, -0.01053, 0.05615, 3.55141
                                   },
                                   .movClass = FALL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.48148, 0.43424, 0.46076, 0.54919, -0.61360, -0.04111, 0.01307, 3.62668
                                   },
                                   .movClass = FALL,
                                   .toSkip = false
                                  },
                                  // FALL RIGHT SIDE
                                  {
                                   .movFeatures = {
                                                   0.62334, 0.45410, 0.20919, -0.55737, -0.51014, 0.01004, 0.11742, 3.12854
                                   },
                                   .movClass = FALL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.57153, 0.44237, 0.33347, -0.46226, -0.62532, 0.13657, 0.10084, 3.32680
                                   },
                                   .movClass = FALL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.56722, 0.37819, 0.33592, -0.49297, -0.61787, -0.03964, 0.15031, 3.04015
                                   },
                                   .movClass = FALL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.58179, 0.36950, 0.26216, -0.42142, -0.69916, -0.10196, 0.07066, 3.39832
                                   },
                                   .movClass = FALL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.53531, 0.40762, 0.39776, -0.44867, -0.59223, -0.12182, 0.07658, 3.36105
                                   },
                                   .movClass = FALL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.56937, 0.43575, 0.28245, -0.50550, -0.57744, 0.02701, 0.10070, 3.09780
                                   },
                                   .movClass = FALL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.56224, 0.46004, 0.32895, -0.45132, -0.57658, 0.07104, 0.15997, 3.41694
                                   },
                                   .movClass = FALL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.53882, 0.42368, 0.34282, -0.55302, -0.49381, -0.15669, 0.07899, 3.01668
                                   },
                                   .movClass = FALL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.53748, 0.39542, 0.26486, -0.42827, -0.66662, -0.09897, 0.13467, 3.28461
                                   },
                                   .movClass = FALL,
                                   .toSkip = false
                                  },
                                  {
                                   .movFeatures = {
                                                   0.52135, 0.47412, 0.40583, -0.45072, -0.55901, 0.22429, 0.13715, 3.46576
                                   },
                                   .movClass = FALL,
                                   .toSkip = false
                                  }
};

void resetDataset(){
    int i;
    for (i = 0; i < DATASET_SIZE; i++){
        dataset[i].toSkip = false;
    }
}
float euclideanDistance(Features f1, Features f2){
    float distance;
    float lpvDistance = pow((f1.lpv - f2.lpv),2);
    float upvDistance = pow((f1.upv - f2.upv),2);
    float xAccelDistance = pow((f1.accMean.x - f2.accMean.x),2);
    float yAccelDistance = pow((f1.accMean.y - f2.accMean.y),2);
    float zAccelDistance = pow((f1.accMean.z - f2.accMean.z),2);
    float xDevDistance = pow((f1.stdDev.x - f2.stdDev.x),2);
    float yDevDistance= pow((f1.stdDev.y - f2.stdDev.y),2);
    float zDevDistance = pow((f1.stdDev.z - f2.stdDev.z),2);
    distance = sqrt(lpvDistance + upvDistance + xAccelDistance + yAccelDistance + zAccelDistance + xDevDistance + yDevDistance + zDevDistance);
    return distance;
}
enum Class classifyMovement(Features peakWindowFeatures, Movement dataset[]){
    float lowerDistance = DEF_SHORTEST_DIST;
    float newDistance;
    int adlCount = 0;
    int fallCount = 0;
    int nearestNeighbour;
    int i,j;
    for (i = 0; i < NEAREST_NEIGHBOURS; i++){
        for (j = 0;j < DATASET_SIZE; j++){
            if (!dataset[j].toSkip){
                newDistance = euclideanDistance(peakWindowFeatures, dataset[j].movFeatures);
                if (newDistance < lowerDistance){
                    lowerDistance = newDistance;
                    nearestNeighbour = j;
                }
            }
        }
        dataset[nearestNeighbour].toSkip = true;
        if (dataset[nearestNeighbour].movClass == ADL)
            adlCount ++;
        else if (dataset[nearestNeighbour].movClass == FALL)
            fallCount ++;
        lowerDistance = DEF_SHORTEST_DIST;
    }
    resetDataset();
    //printf("%d, %d\n", adlCount, fallCount);
    return (fallCount >= adlCount) ? FALL : ADL;
}
Features computeWindowFeatures(int start, int stop){
    Features newFeatures;
    float newAcc;
    float lowerAcc;
    float upperAcc;
    int windowIndex;
    Sample mean = {0, 0, 0};
    Sample variance = {0, 0, 0};
    Sample stdDev = {0, 0, 0};
    bool firstIteration = true;

    if (start > stop){
        stop += BUFFER_SIZE;
    }

    /* compute mean acceleration for every axis */
    for (windowIndex = start; windowIndex < stop; windowIndex ++){
        mean.x += circularBuffer[windowIndex % BUFFER_SIZE].x;
        mean.y += circularBuffer[windowIndex % BUFFER_SIZE].y;
        mean.z += circularBuffer[windowIndex % BUFFER_SIZE].z;
    }
    mean.x /= WINDOW_SIZE;
    mean.y /= WINDOW_SIZE;
    mean.z /= WINDOW_SIZE;
    /* compute variance of acceleration for every axis */
    for (windowIndex = start; windowIndex < stop; windowIndex ++){
        variance.x += pow(circularBuffer[windowIndex % BUFFER_SIZE].x - mean.x, 2);
        variance.y += pow(circularBuffer[windowIndex % BUFFER_SIZE].y - mean.y, 2);
        variance.z += pow(circularBuffer[windowIndex % BUFFER_SIZE].z - mean.z, 2);
    }
    variance.x /= WINDOW_SIZE;
    variance.y /= WINDOW_SIZE;
    variance.z /= WINDOW_SIZE;
    /* compute standard deviation for every axis */
    stdDev.x = sqrt(variance.x);
    stdDev.y = sqrt(variance.y);
    stdDev.z = sqrt(variance.z);

    /* compute lower and higher acceleration peaks */
    for (windowIndex = start; windowIndex < stop; windowIndex ++){
        newAcc = sqrt(pow(circularBuffer[windowIndex % BUFFER_SIZE].x, 2) + pow(circularBuffer[windowIndex % BUFFER_SIZE].y, 2) + pow(circularBuffer[windowIndex % BUFFER_SIZE].z, 2));
        if(firstIteration){
            lowerAcc = newAcc;
            upperAcc = newAcc;
            firstIteration = false;
        } else {
            if (newAcc < lowerAcc){
                lowerAcc = newAcc;
            } else if (newAcc > upperAcc){
                upperAcc = newAcc;
            }
        }
    }
    newFeatures.accMean = mean;
    newFeatures.stdDev = stdDev;
    newFeatures.lpv = lowerAcc;
    newFeatures.upv = upperAcc;
    return newFeatures;
}
bool isPeak(Sample sample){
    float sampleAcc = sqrt(pow(sample.x, 2) + pow(sample.y, 2) + pow(sample.z, 2));
    return (sampleAcc < LOWER_THRESHOLD || sampleAcc > UPPER_THRESHOLD) ? true : false;
}
Sample getRawSample(){
    Sample rawSample;
    rawSample.x = ADC14_getResult(ADC_MEM0);
    rawSample.y = ADC14_getResult(ADC_MEM1);
    rawSample.z = ADC14_getResult(ADC_MEM2);
    return rawSample;
}
Sample convertRawSample(Sample rawSample){
    Sample convertedSample;
    convertedSample.x = (((rawSample.x * ADC_REF_VOLTAGE) / ADC_INPUT_RANGE) - ACC_OFFSET) / ACC_SENSITIVITY;
    convertedSample.y = (((rawSample.y * ADC_REF_VOLTAGE) / ADC_INPUT_RANGE) - ACC_OFFSET) / ACC_SENSITIVITY;
    convertedSample.z = (((rawSample.z * ADC_REF_VOLTAGE) / ADC_INPUT_RANGE) - ACC_OFFSET) / ACC_SENSITIVITY;
    return convertedSample;
}
void storeNewSample(){
    Sample newRawSample = getRawSample();
    Sample newConvertedSample = convertRawSample(newRawSample);
    circularBuffer[bufferIndex] = newConvertedSample;
}
void computeWindowRange(){
    if ((bufferIndex - WINDOW_SIZE + 1) < 0){
        stopIndex = bufferIndex;
        startIndex = BUFFER_SIZE + (stopIndex - WINDOW_SIZE + 1);
    } else {
        stopIndex = bufferIndex;
        startIndex = stopIndex - WINDOW_SIZE + 1;
    }
}
void updateIndex(){
    bufferIndex = (bufferIndex + 1 == BUFFER_SIZE) ? 0 : bufferIndex + 1;
}
void updateProgramState(){
    currentState = nextState;
}
void doProgramState(){
    switch(currentState){
        case SEARCHING_FOR_PEAK:
            updateIndex();
            storeNewSample();
            if (isPeak(circularBuffer[bufferIndex])){
                nextState = FILLING_PEAK_WINDOW;
                missingSamples = WINDOW_SIZE / 2;
            }
            break;
        case FILLING_PEAK_WINDOW:
            if (missingSamples > 0){
                updateIndex();
                storeNewSample();
                missingSamples --;
            } else if (missingSamples == 0){
                nextState = CLASSIFYING_PEAK_WINDOW;
            }
            break;
        case CLASSIFYING_PEAK_WINDOW:
        {
            computeWindowRange();
            Features peakWindowFeatures = computeWindowFeatures(startIndex, stopIndex);
            enum Class predictedMovement = classifyMovement(peakWindowFeatures, dataset);
            if (predictedMovement == FALL){
                canClassify = false;
                clearDisplay();
                displayWarningPage();
            }
            nextState = SEARCHING_FOR_PEAK;
            break;
        }
        default:
            break;
        }
    updateProgramState();
}

