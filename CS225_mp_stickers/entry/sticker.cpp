#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image pic;
  Image stick1;
  Image stick2;
  Image stick3;

  pic.readFromFile("../data/alma.png");
  stick1.readFromFile("../data/i.png");
  stick2.readFromFile("../data/penguin.png");
  stick3.readFromFile("../data/i.png");

  StickerSheet pt3(pic, 3);
  pt3.addSticker(stick1, 200, 200);
  pt3.addSticker(stick2, 0, 0);
  pt3.addSticker(stick3, 400, 400);
  Image ret = pt3.render();
  ret.writeToFile("myImage.png");
  return 0;
}
