#define _WORLD_MATRIX

#ifdef _EXERCIZE
#include"libOne.h"
void gmain() {
    window(1000, 1000);
    while (notQuit) {
    }
}
#endif
#ifdef _COORDINATE_DIRECTX
#include"libOne.h"
void gmain() {
    window(1000, 1000);
    VECTOR p[3];
    p[0].set(-1, 1, 0);
    p[1].set(-1, -1, 0);
    p[2].set(1, -1, 0);
    while (notQuit) {
        clear();
        triangle3D(p[0], p[1], p[2]);
    }
}
#endif
#ifdef _COORDINATE_MATH1
#include"libOne.h"
void gmain() {
    window(1000, 1000);
    const int numVertices = 3;
    VECTOR op[numVertices];
    op[0].set(0, 1, 0);
    op[1].set(-1, -1, 0);
    op[2].set(1, -1, 0);
    VECTOR p[numVertices];
    float angle = 0;
    while (notQuit) {
        clear(60);
        float c = cos(angle);
        angle += 0.017f;
        for (int i = 0; i < numVertices; i++) {
            //world座標変換
            p[i].x = op[i].x;
            p[i].y = op[i].y;
            p[i].z = op[i].z - 2 + c;
            //projection座標変換
            p[i].z *= -1;
            p[i].x /= p[i].z;
            p[i].y /= p[i].z;
            p[i].z /= 5;
        }
        triangle3D(p[0], p[1], p[2]);
    }
}
#endif
#ifdef _COORDINATE_MATH2
#include"libOne.h"
void gmain() {
    window(1000, 1000);
    const int numVertices = 4;
    VECTOR op[numVertices];
    op[0].set(-0.5f,0.5f,0);
    op[1].set(-0.5f,-0.5f,0);
    op[2].set(0.5f,0.5f,0);
    op[3].set(0.5f,-0.5f,0);
    VECTOR p[numVertices];
    float angle = 0;
    int sw = 0;
    while (notQuit) {
        clear(60);
        if (isTrigger(KEY_SPACE))++sw %= 5;
        float s = sin(angle);
        float c = cos(angle);
        angle += 0.04f;
        //tz += -0.05f;
        for (int i = 0; i < numVertices; i++) {
            //ワールド座標変換
            if (sw == 0) {
                p[i].x = op[i].x * c + op[i].y * -s;
                p[i].y = op[i].x * s + op[i].y * c;
                p[i].z = op[i].z;
            }
            else if (sw == 1) {
                p[i].x = op[i].x * c + op[i].z * s;
                p[i].y = op[i].y;
                p[i].z = op[i].x * -s + op[i].z * c;
            }
            else if (sw == 2) {
                p[i].x = op[i].x;
                p[i].y = op[i].y * c + op[i].z * -s;
                p[i].z = op[i].y * s + op[i].z * c;
            }
            else if (sw == 3) {
                p[i].x = op[i].x * (c + 1.5f);
                p[i].y = op[i].y;
                p[i].z = op[i].z;
            }
            else if (sw == 4) {
                p[i].x = op[i].x;
                p[i].y = op[i].y;
                p[i].z = op[i].z + (c-1);
            }
            p[i].z += -2;
            //プロジェクション座標変換
            if (p[i].z < 0) {
                p[i].z *= -1;
                p[i].x /= p[i].z;
                p[i].y /= p[i].z;
                p[i].z /= 20;
            }
        }
        triangle3D(p[0], p[1], p[2]);
        triangle3D(p[2], p[1], p[3]);
    }
}
#endif
#ifdef _WORLD_MATRIX
#include"libOne.h"
void gmain() {
    window(900, 900);
    const int numVertices = 4;
    VECTOR op[numVertices];
    op[0].set(-0.5f, 0.5f, 0);
    op[1].set(-0.5f, -0.5f, 0);
    op[2].set(0.5f, 0.5f, 0);
    op[3].set(0.5f, -0.5f, 0);
    VECTOR p[numVertices];
    MATRIX world;
    float angle = 0;
    while (notQuit) {
        clear(60);

        world.identity();
        world.mulTranslate(0, 0, -1);
        world.mulRotateX(angle);
        world.mulTranslate(0, 3, 0);
        angle += 0.017f;

        for (int i = 0; i < numVertices; i++) {
            //ワールド座標変換
            p[i] = world * op[i];
            //プロジェクション座標変換
            if (p[i].z < 0) {
                p[i].z *= -1;
                p[i].x /= p[i].z;
                p[i].y /= p[i].z;
                p[i].z /= 20;
            }
        }

        triangle3D(p[0], p[1], p[2]);
        triangle3D(p[2], p[1], p[3]);
    }
}
#endif
#ifdef _TANJIRO_FLOOR
#include"libOne.h"
void gmain() {
    window(1000, 1000);
    const int numVertices = 4;
    VECTOR op[numVertices];
    op[0].set(-0.5, 0.5, 0);
    op[1].set(-0.5, -0.5, 0);
    op[2].set(0.5, 0.5, 0);
    op[3].set(0.5, -0.5, 0);
    VECTOR p[numVertices];
    MATRIX parent;
    MATRIX world;
    float angle = 0;
    COLOR c[2];
    c[0].set(0, 0, 0);
    c[1].set(0, 128, 0);
    while (notQuit) {
        clear(200,200,0);
        parent.identity();
        parent.mulTranslate(0, -1, -2);
        parent.mulRotateY(angle);
        parent.mulRotateX(1.57f);
        parent.mulTranslate(-4, -4, 0);
        angle += 0.005f;
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                //ワールド座標変換行列をつくる
                world.identity();
                world.mulTranslate(col, row, 0);
                world = parent * world;
                for (int i = 0; i < numVertices; i++) {
                    //ワールド座標変換
                    p[i] = world * op[i];
                    //プロジェクション座標変換
                    if (p[i].z < 0) {
                        p[i].z *= -1;
                        p[i].x /= p[i].z;
                        p[i].y /= p[i].z;
                        p[i].z = map(p[i].z, 0.0f, 20.0f, 0.0f, 1.0f);
                    }
                }
                int no = (row + col) % 2;
                triangle3D(p[0], p[1], p[2], c[no], c[no], c[no]);
                triangle3D(p[2], p[1], p[3], c[no], c[no], c[no]);
            }
        }
    }
}
#endif
