#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Score {
public:
    Score(); // Constructor
    ~Score(); // Destructor de giai phóng tài nguyên
    void init(SDL_Renderer* renderer); // Khoi tao he thong hien thi diem so
    void update(int newScore); // Cap nhat diem so moi
    void render(SDL_Renderer* renderer, bool gameOver); // Hien thi diem so lên màn hình, thêm gameOver
    void free(); // Giai phóng bo nho

private:
    int score; // Bien luu diem so hien tai
    TTF_Font* font; // Font chu de hien thi diem so
    SDL_Texture* texture; // Texture chua hình anh diem so
    SDL_Rect scoreRect; // Kích thuoc và va trí cua diem so trên màn hình
    SDL_Color color; // Màu cua chu diem so
    SDL_Renderer* renderer; // Con tro tai SDL_Renderer de ve lên màn hình

    // Thêm biến cho Game Over
    SDL_Texture* gameOverTexture;
    SDL_Rect gameOverRect;

    void updateTexture(); // Cap nhat texture khi diem so thay doi
    void renderGameOver(SDL_Renderer* renderer); // Hien thi chữ "Game Over"
};

#endif // SCORE_H_INCLUDED
