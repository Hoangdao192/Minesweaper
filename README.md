# Bài tập lớn môn Lập trình nâng cao - Trường đại học Công nghệ - Đại học Quốc gia Hà Nội (UET)

# Minesweaper - Dò mìn

## Sử dụng
  - C++
  - SDL2

Xem mã nguồn của game trong folder SourceCode
Chạy game để chơi trong folder GameRelease (trong đây chứ file readme và hướng dẫn cài đặt riêng)

(Nếu bạn chỉ chạy game thì không cần cài thêm các thư viện bên dưới)
Để code chạy được, cần cài đặt các thư viện sau (kèm link hướng dẫn cài đặt)
- SDL.h:
  https://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php
- SDL_image.h
  https://lazyfoo.net/tutorials/SDL/06_extension_libraries_and_loading_other_image_formats/index.php
- SDL_ttf.h
  http://www.libsdl.org/projects/SDL_ttf/ (link tải)
  cài đặt giống như cài đặt SDL_image
  CodeBlock: Setting -> Compiler -> Global Compiler Setting -> Linker settings -> Other linker option
  thêm: -lSDL2_ttf
  -> OK
   -lSDL2_mixer -lSDL2_ttf
- SDL_mixer.h
  http://www.libsdl.org/projects/SDL_mixer/ (link tải)
  cài đặt giống như SDL_ttf
  thêm dòng: -lSDL2_mixer vào Other linker option giống như khi cài SDL_ttf
  
Các cấu trúc cơ bản của game:
- class ButtonObject: xử lý các nút bấm
- class ImageObject: xử lý hình ảnh (lưu hình ảnh, kích thước gốc và kích thước khi vẽ ra màn hình)
- class TextObject: xử lý chữ vẽ ra màn hình
- class SquareObject: xử lý các ô vuông
- MainFunction.h: chứa các hàm xử lý chung
- MainVariable.h: chứa các giá trị chung
- Game.h Game.cpp: xử lý game
- Menu: xử lý menu chính
- Setting: xử lý  menu cài đặt chính
- Quick_setting: xử lý menu cài đặt nhanh
- SetGameDifficulty: xủ lý menu cài đặt độ khó
- Custom_difficulty: xử lý menu cài đặt độ khó tùy chọn
- SetGameMode: xử lý menu cài đặt chế độ chơi
