#include "pipe.h"
#include <stdlib.h>
#include <time.h>
#include <SDL_image.h>

Pipe pipes[2];
SDL_Texture* pipeBodyTexture = NULL;  // Texture cho thân ong
SDL_Texture* pipeHeadTexture = NULL;  // Texture cho mieng ong

// Tai hình anh ong nuoc
void loadPipeTexture(SDL_Renderer* renderer) {
    SDL_Surface* bodySurface = IMG_Load("pipe_body.png");
    if (bodySurface) {
        pipeBodyTexture = SDL_CreateTextureFromSurface(renderer, bodySurface);
        SDL_FreeSurface(bodySurface);
    }
    SDL_Surface* headSurface = IMG_Load("pipe_head.png");
    if (headSurface) {
        pipeHeadTexture = SDL_CreateTextureFromSurface(renderer, headSurface);
        SDL_FreeSurface(headSurface);
    }
}

// Khoi tao vi trí ban dau cua các ong nuoc
void initPipes(SDL_Renderer* renderer) {
    srand(time(NULL));

    int minHeight = 50;
    int maxHeight = SCREEN_HEIGHT - PIPE_GAP - 50;

    pipes[0].x = SCREEN_WIDTH;
    pipes[0].height = minHeight + rand() % (maxHeight - minHeight + 1);
    pipes[1].x = SCREEN_WIDTH + SCREEN_WIDTH / 2;
    pipes[1].height = minHeight + rand() % (maxHeight - minHeight + 1);

    loadPipeTexture(renderer);
}

// Cap nhat vi trí cua các ong nuoc và kiem tra va cham
void updatePipes(bool* gameOver, int* score, int birdX, int birdY, int birdSize) {
    int minHeight = 50;
    int maxHeight = SCREEN_HEIGHT - PIPE_GAP - 50;

    for (int i = 0; i < 2; i++) {
        pipes[i].x -= 5;

        // Reset vị trí ống nước khi nó ra khỏi màn hình
        if (pipes[i].x + PIPE_WIDTH < 0) {
            pipes[i].x = SCREEN_WIDTH;
            pipes[i].height = minHeight + rand() % (maxHeight - minHeight + 1);
            pipes[i].passed = false; // Reset trạng thái
        }

        // Cập nhật điểm khi chim vượt qua ống
        if (birdX > pipes[i].x + PIPE_WIDTH && !pipes[i].passed) {
            pipes[i].passed = true; // Đánh dấu đã qua ống
            (*score)++;
        }

        // Kiểm tra va chạm chính xác
        int collisionBuffer = 3; // Điều chỉnh nhỏ hơn nếu cần
        int bottomPipeY = pipes[i].height + PIPE_GAP;

        bool hitTopPipe = (birdY + collisionBuffer < pipes[i].height);
        bool hitBottomPipe = (birdY + birdSize - collisionBuffer > bottomPipeY);

        if (birdX + birdSize - collisionBuffer > pipes[i].x &&
            birdX + collisionBuffer < pipes[i].x + PIPE_WIDTH &&
            (hitTopPipe || hitBottomPipe)) {
            *gameOver = true;
            return;
        }
    }
}

// Ve ong nuoc lên màn hình
void renderPipes(SDL_Renderer* renderer) {
    if (pipeBodyTexture && pipeHeadTexture) {
        const int HEAD_HEIGHT = 20;    // Chieu cao mieng ong (giu nguyên nhu truoc)
        const int HEAD_WIDTH = PIPE_WIDTH + 10;  // Chieu ngang mieng ong dài hon PIPE_WIDTH mot chút

        for (int i = 0; i < 2; i++) {
            // ong trên
            // Thân ong trên (giu nguyên PIPE_WIDTH)
            SDL_Rect upperBody = { pipes[i].x, 0, PIPE_WIDTH, pipes[i].height - HEAD_HEIGHT };
            SDL_RenderCopyEx(renderer, pipeBodyTexture, NULL, &upperBody, 0, NULL, SDL_FLIP_VERTICAL);
            // Mieng ong trên (kéo dài chieu ngang)
            SDL_Rect upperHead = { pipes[i].x - 5, pipes[i].height - HEAD_HEIGHT, HEAD_WIDTH, HEAD_HEIGHT };  // Dịch trái 5 để căn giữa
            SDL_RenderCopyEx(renderer, pipeHeadTexture, NULL, &upperHead, 0, NULL, SDL_FLIP_VERTICAL);

            // ong duoi
            // Thân ong duoi (giu nguyên PIPE_WIDTH)
            SDL_Rect lowerBody = { pipes[i].x, pipes[i].height + PIPE_GAP + HEAD_HEIGHT, PIPE_WIDTH, SCREEN_HEIGHT - (pipes[i].height + PIPE_GAP + HEAD_HEIGHT) };
            SDL_RenderCopy(renderer, pipeBodyTexture, NULL, &lowerBody);
            // Mieng ong duoi (kéo dài chieu ngang)
            SDL_Rect lowerHead = { pipes[i].x - 5, pipes[i].height + PIPE_GAP, HEAD_WIDTH, HEAD_HEIGHT };  // Dịch trái 5 để căn giữa
            SDL_RenderCopy(renderer, pipeHeadTexture, NULL, &lowerHead);
        }
    }
}

// Giai phóng tài nguyên liên quan den ong nuoc
void freePipes() {
    if (pipeBodyTexture) {
        SDL_DestroyTexture(pipeBodyTexture);
        pipeBodyTexture = NULL;
    }
    if (pipeHeadTexture) {
        SDL_DestroyTexture(pipeHeadTexture);
        pipeHeadTexture = NULL;
    }
}
