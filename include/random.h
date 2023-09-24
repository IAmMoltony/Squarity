#ifndef RANDOM_H
#define RANDOM_H

#ifdef __cplusplus
extern "C" {
#endif

void RandomInit(void);
int RandomRange(int min, int max);

#ifdef __cplusplus
}
#endif

#endif // RANDOM_H
