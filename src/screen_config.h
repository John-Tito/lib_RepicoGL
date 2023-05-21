//
// Created by kaaass on 2020/3/16.
//

#ifndef PICOGL_TEST_SCREEN_CONFIG_H
#define PICOGL_TEST_SCREEN_CONFIG_H
#define USER_SCREEN_CONFIG
#ifndef USER_SCREEN_CONFIG
#error "set your screen config here"
#endif
#warning "Change to your screen resolution"
#define SCREEN_WIDTH 130
#define SCREEN_HEIGHT 130
#define SCREEN_BITS_PER_PIXEL 16
#define SCREEN_LINE_BYTES_LENGTH (SCREEN_WIDTH * SCREEN_BITS_PER_PIXEL / 8)

#endif //PICOGL_TEST_SCREEN_CONFIG_H
