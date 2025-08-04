#include <SDL2/SDL.h>
#include <iostream>

// 화면 크기 상수
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char* args[]) {
    // SDL 초기화
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL을 초기화할 수 없습니다! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // 윈도우 생성
    SDL_Window* window = SDL_CreateWindow(
        "SDL2 C++ 예제",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    
    if (window == nullptr) {
        std::cout << "윈도우를 생성할 수 없습니다! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // 렌더러 생성
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, 
        -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    
    if (renderer == nullptr) {
        std::cout << "렌더러를 생성할 수 없습니다! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // 이벤트 핸들러
    SDL_Event e;
    bool quit = false;

    // 메인 루프
    while (!quit) {
        // 이벤트 처리
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // 화면을 파란색으로 칠하기
        SDL_SetRenderDrawColor(renderer, 0x00, 0x7F, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        // 빨간 사각형 그리기
        SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(renderer, &fillRect);

        // 초록 윤곽선 그리기
        SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
        SDL_RenderDrawRect(renderer, &outlineRect);

        // 노란 선 그리기
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
        SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

        // 화면 업데이트
        SDL_RenderPresent(renderer);
    }

    // 리소스 정리
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
