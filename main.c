#include <math.h>
#include <raylib.h>

float width;
float height;

float x_zoom;
float y_zoom;

float x_shift;
float y_shift;

typedef struct {
    int posX, posY, width, height;
    Color color;
} Args;

void InitGlobals() {
    width = 1280;
    height = 720;

    x_zoom = 4;
    y_zoom = 3;

    x_shift = 2.5f;
    y_shift = 1.5f;
}

Vector2 pixToCoord(float x, float y) {
    return (Vector2) {
        x / (width / x_zoom) - x_shift,
        (y / (height / y_zoom) - y_shift) * -1
    };
}

float square(float x) {
    return x * x;
}

Color getColor(int x, int y) {
    int n = 0;
    const Vector2 c = pixToCoord(x, y);

    Vector2 z = {
        0,
        0
    };

    Vector2 zSquare = {
        0,
        0
    };

    while (zSquare.x + zSquare.y <= 4 && n < 1000) {
        zSquare.x =z.x * z.x;
        zSquare.y =z.y * z.y;

        z.y = (z.x + z.x) * z.y + c.y;
        z.x = zSquare.x - zSquare.y + c.x;
        n++;
    }

    if (zSquare.x + zSquare.y <= 4) {
        return BLACK;
    }

    return ColorFromHSV((int) (pow((n / 1000.0) * 360, 1.5)) % 360, 100, (n / 1000.0) * 100);
}

void drawFract() {
    BeginDrawing();

    DrawFPS(20, 20);

    ClearBackground(BLACK);
    for (int y = 0; y < height; y += 3) {
        for (int x = 0; x < width; x += 3) {
            Color c = getColor(x, y);
            DrawRectangle(x, y, 3, 3, c);
        }
    }

    EndDrawing();
}

int main() {
    InitGlobals();
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(width, height, "Mandelbrot Visualisierung");

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        if (IsWindowResized()) {
            height = GetScreenHeight();
            width = GetScreenWidth();
        }

        if (IsKeyDown(KEY_RIGHT))
            x_shift /= 1.01f;
        if (IsKeyDown(KEY_LEFT))
            x_shift *= 1.01f;
        if (IsKeyDown(KEY_UP))
            y_shift *= 1.01f;
        if (IsKeyDown(KEY_DOWN))
            y_shift /= 1.01f;
        if (IsKeyDown(KEY_RIGHT_BRACKET)) {
            x_zoom /= 1.08f;
            y_zoom /= 1.08f;
        }
        if (IsKeyDown(KEY_SLASH)) {
            x_zoom *= 1.08f;
            y_zoom *= 1.08f;
        }
        if (IsKeyPressed(KEY_R)) {
            x_zoom = 4;
            y_zoom = 3;
            x_shift = 2.5f;
            y_shift = 1.5f;
        }

        drawFract();
    }
}