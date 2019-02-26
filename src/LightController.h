#ifndef LIGHTCONTROLLER_H
#define LIGHTCONTROLLER_H

#define MAX_LIGHTS 32

void LightController_Create(void);
void LightController_Destroy(void);
void LightController_On(int id);
void LightController_Off(int id);

#endif /* LIGHTCONTROLLER_H */
