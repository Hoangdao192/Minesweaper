*******CHƠI GAME****************
Game có giao diện đồ họa
Game có 2 chế độ chơi là Cổ điển và Đếm ngược
Game có các độ khó khác nhau và có thể tùy chỉnh

Có thể tùy chỉnh độ phân giải màn hình
Có thể bật tắt âm thanh 

Cách chơi:
-	Bấm chuột trái để mở một ô
-	Bấm chuột phải để đặt và xóa cờ
-	Bấm biểu tượng dấu hỏi để được trợ giúp
-	Bấm biểu tượng cài đặt để Tạm dừng cũng như sử dụng menu cài đặt nhanh
-	Chế độ cổ điển: Mở trúng ô bom sẽ thua, mở hết các ô không có bom sẽ thắng
-	Chế độ đếm ngược: cơ bản giống với cổ điển nhưng bị giới hạn thời gian chờ
	+ bạn sẽ thua nếu để thời gian đếm ngược kết thúc
	+liên tục mở ô sẽ reset thời gian đếm ngược
Luật chơi:
	- Số điểm của 1 ô là số bom nằm xung quanh ô đó
	- Ô không có điểm tức là không có bom xung quanh
	- Chế độ cổ điển: Mở trúng ô bom sẽ thua, mở hết các ô không có bom sẽ thắng
	- Chế độ đếm ngược: cơ bản giống với cổ điển nhưng bị giới hạn thời gian chờ
	+ bạn sẽ thua nếu để thời gian đếm ngược kết thúc
	+liên tục mở ô sẽ reset thời gian đếm ngược
Bạn sẽ không bị thua  ngay trong lần mở ô đầu tiên

*************XEM MÃ NGUỒN*******************
Để code chạy được, cần cài đặt các thư viện sau (kèm link hướng dẫn cài đặt)

SDL.h: https://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php
SDL_image.h https://lazyfoo.net/tutorials/SDL/06_extension_libraries_and_loading_other_image_formats/index.php
SDL_ttf.h http://www.libsdl.org/projects/SDL_ttf/ (link tải) cài đặt giống như cài đặt SDL_image CodeBlock: Setting -> Compiler -> Global Compiler Setting -> Linker settings -> Other linker option thêm: -lSDL2_ttf -> OK -lSDL2_mixer -lSDL2_ttf
SDL_mixer.h http://www.libsdl.org/projects/SDL_mixer/ (link tải) cài đặt giống như SDL_ttf thêm dòng: -lSDL2_mixer vào Other linker option giống như khi cài SDL_ttf

Các cấu trúc cơ bản của game:
class ButtonObject: xử lý các nút bấm
class ImageObject: xử lý hình ảnh (lưu hình ảnh, kích thước gốc và kích thước khi vẽ ra màn hình)
class TextObject: xử lý chữ vẽ ra màn hình
class SquareObject: xử lý các ô vuông
MainFunction.h: chứa các hàm xử lý chung
MainVariable.h: chứa các giá trị chung
Game.h Game.cpp: xử lý game
Menu: xử lý menu chính
Setting: xử lý menu cài đặt chính
Quick_setting: xử lý menu cài đặt nhanh
SetGameDifficulty: xủ lý menu cài đặt độ khó
Custom_difficulty: xử lý menu cài đặt độ khó tùy chọn
SetGameMode: xử lý menu cài đặt chế độ chơi

