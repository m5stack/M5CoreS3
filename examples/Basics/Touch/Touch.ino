#include <M5Unified.h>

#include <esp_log.h>

void setup(void)
{
  M5.begin();
  M5.Display.setTextSize(2);
}

void loop(void)
{
  vTaskDelay(500);

  M5.update();

  M5.Display.clear();
  auto count = M5.Touch.getCount();
  if(count)
  {
    M5.Display.setCursor(0,0);
    M5.Display.print("touch"); 

    M5.Display.setCursor(0, 20);
    M5.Display.print(M5.Touch.getDetail(0).x); 

    M5.Display.setCursor(0, 40);
    M5.Display.print(M5.Touch.getDetail(0).y); 
  }
  else
  {
    M5.Display.setCursor(0, 20);
    M5.Display.print(0); 

    M5.Display.setCursor(0, 40);
    M5.Display.print(0); 
  }


  M5.Display.display();
}

#if !defined ( ARDUINO )
extern "C" {
  void loopTask(void*)
  {
    setup();
    for (;;) {
      loop();
    }
    vTaskDelete(NULL);
  }

  void app_main()
  {
    xTaskCreatePinnedToCore(loopTask, "loopTask", 8192, NULL, 1, NULL, 1);
  }
}
#endif
