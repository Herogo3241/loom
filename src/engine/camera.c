#include "camera.h"

void init_camera(Camera *c, vec3 position){
    glm_vec3_copy(position, c->position);
    glm_vec3_copy((vec3){0.0f, 1.0f, 0.0f}, c->world_up);

    c->yaw = YAW;
    c->pitch = PITCH;
    c->speed = SPEED;
    c->sensitivity = SENSITIVITY;

    glm_vec3_copy((vec3){0.0f, 0.0f, -0.0f}, c->front);
    camera_update_vectors(c);

}

void camera_get_view_matrix(Camera *c, mat4 view){
    vec3 target;
    glm_vec3_add(c->position, c->front, target);
    glm_lookat(c->position, target, c->world_up, view);
}


void camera_process_keyboard(Camera *c, Camera_Movement direction, float delta){
    float velocity = c->speed * delta;
    vec3 movement;

    if (direction == CAMERA_FORWARD) {
        glm_vec3_scale(c->front, velocity, movement);
        glm_vec3_add(c->position, movement, c->position); 
    }
    if (direction == CAMERA_BACKWARD) { 
        glm_vec3_scale(c->front, velocity, movement);
        glm_vec3_sub(c->position, movement, c->position); 
    }

    if (direction == CAMERA_RIGHT) { 
        glm_vec3_scale(c->right, velocity, movement);
        glm_vec3_add(c->position, movement, c->position); 
    }
    if (direction == CAMERA_LEFT) { 
        glm_vec3_scale(c->right, velocity, movement);
        glm_vec3_sub(c->position, movement, c->position); 
    }


}


void camera_process_mouse(Camera *c, float x_offset, float y_offset,float delta, bool constrain_pitch){
    x_offset *= c->sensitivity * delta * 100.f;
    y_offset *= c->sensitivity * delta * 100.f;


    c->yaw += x_offset;
    c->pitch += y_offset;
    if (constrain_pitch) {
        if (c->pitch > 89.0f)  c->pitch = 89.0f;
        if (c->pitch < -89.0f) c->pitch = -89.0f;
    }
    camera_update_vectors(c);

}


void camera_update_vectors(Camera *c){
    vec3 front;
    front[0] = cosf(glm_rad(c->yaw)) * cosf(glm_rad(c->pitch));
    front[1] = sinf(glm_rad(c->pitch));
    front[2] = sinf(glm_rad(c->yaw)) * cosf(glm_rad(c->pitch));
    glm_vec3_normalize_to(front, c->front);

    glm_vec3_cross(c->front, c->world_up, c->right);
    glm_vec3_normalize(c->right);

    glm_vec3_cross(c->right, c->front, c->up);
    glm_vec3_normalize(c->up);

}

void camera_set_sensitivity(Camera *c, float value){
    c->sensitivity = value;
}
