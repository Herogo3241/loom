#ifndef CAMERA_H
#define CAMERA_H

#include <cglm/cglm.h>

typedef enum{
    CAMERA_FORWARD,
    CAMERA_BACKWARD,
    CAMERA_RIGHT,
    CAMERA_LEFT
}Camera_Movement;

//default values
#define YAW -90.0f
#define PITCH 0.0f
#define SPEED 2.5f
#define SENSITIVITY 0.1f

typedef struct{
    vec3 position;
    vec3 front;
    vec3 right;
    vec3 up;
    vec3 world_up;

    float yaw;
    float pitch;

    float speed;
    float sensitivity;
}Camera;

void init_camera(Camera* c, vec3 position);

void camera_get_view_matrix(Camera* c, mat4 view);

void camera_process_keyboard(Camera* c, Camera_Movement direction, float delta);

void camera_process_mouse(Camera* c, float x_offset, float y_offset, bool constrain_pitch);

void camera_update_vectors(Camera* c);



#endif 
