int start_pin = 2;
int count_pins = 16;

void print_scene(bool scene[], int _delay) {
  for (int i=0; i < count_pins; i++) {
     digitalWrite(start_pin+i, !scene[i]?HIGH:LOW);
     Serial.print(scene[i]?"H":"L");
     Serial.print(",");
  }
  Serial.println();
  delay(_delay);
}

void scene_1() {
  Serial.println("Scene 1");
  bool _step[count_pins];
  for (int i1=0; i1 < count_pins; i1++) {
    _step[i1] = false;
  }
  for (int i2=0; i2 < count_pins; i2++) {
    _step[i2] = true;
    if (i2>0){
      _step[i2-1] = false;
    }else{
      _step[count_pins-1] = false;
    }
    print_scene(_step,200);
  }
}

void scene_2() {
  Serial.println("Scene 2");
  bool _step[count_pins];
  for (int i1=0; i1 < count_pins; i1++) {
    _step[i1] = false;
  }
  for (int i2=0; i2 < count_pins; i2=i2+2) {
    _step[i2] = true;
    if (i2>0){
      _step[i2-2] = false;
    }else{
      _step[count_pins-1] = false;
    }
    print_scene(_step,200);
  }
}

void scene_3() {
  Serial.println("Scene 3");
  bool _step[count_pins];
  int rand_value;
  for (int i1=0; i1 < count_pins; i1++) {
    _step[i1] = (random(0,2) == 1)?true:false;
  }
  print_scene(_step,50);
}

void strobo(int _delay) {
  Serial.println("Scene 3");
  bool _step[count_pins];
  for (int veces=0; veces < random(50,300); veces++) {
    for (int i1=0; i1 < count_pins; i1++) {
      _step[i1] = false;
    }
    print_scene(_step,_delay);
    for (int i2=0; i2 < count_pins; i2++) {
      _step[i2] = true;
    }
    print_scene(_step,_delay);
  }
}

void vibra(int _vibraciones, int _velocidad){
  bool _scene[count_pins];
  for (int veces=0; veces < random(10,50); veces++) {
    for (int i1=0; i1 < count_pins; i1++) {
      _scene[i1] = false;
    }
    print_scene(_scene,0);
    int luz = random(0,count_pins-1);
    for (int i2=0; i2 < random(0,_vibraciones); i2++) {
      _scene[luz] = !_scene[luz];
      print_scene(_scene,random(_velocidad,_velocidad*4));
    }
  }
}

void al_centro_y_vuelta(int _velocidad){
  bool _scene[count_pins];
  for (int i2=0; i2 < count_pins; i2++) {
    for (int i1=0; i1 < count_pins-1; i1++) {
      _scene[i1] = false;
    }
    _scene[i2] = true;
    _scene[count_pins-i2-2] = true;
    print_scene(_scene,_velocidad);
  }
}

void al_centro(int _velocidad){
  bool _scene[count_pins];
  for (int i2=0; i2 < count_pins/2; i2++) {
    for (int i1=0; i1 < count_pins-1; i1++) {
      _scene[i1] = false;
    }
    _scene[i2] = true;
    _scene[count_pins-i2-2] = true;
    print_scene(_scene,_velocidad);
  }
}

void para_afuera(int _velocidad){
  bool _scene[count_pins];
  for (int i2=0; i2 < count_pins/2; i2++) {
    for (int i1=0; i1 < count_pins-1; i1++) {
      _scene[i1] = false;
    }
    _scene[count_pins/2-i2] = true;
    _scene[count_pins/2+i2] = true;
    print_scene(_scene,_velocidad);
  }
}

void cosa_1(int _velocidad){
  bool _scene[count_pins];
  for (int i2=0; i2 < count_pins; i2++) {
    for (int i1=0; i1 < count_pins-1; i1++) {
      _scene[i1] = false;
    }
    _scene[count_pins-1/2-i2] = true;
    _scene[count_pins-1/2+i2-2] = true;
    print_scene(_scene,_velocidad);
  }
}

void silencio(int _tiempo){
  Serial.println("silencio");
  bool _scene[count_pins];
  for (int i1=0; i1 < count_pins-1; i1++) {
    _scene[i1] = false;
  }
  print_scene(_scene,_tiempo);
}

void pleno(int _tiempo){
  Serial.println("silencio");
  bool _scene[count_pins];
  for (int i1=0; i1 < count_pins-1; i1++) {
    _scene[i1] = true;
  }
  print_scene(_scene,_tiempo);
}

void setup() {
  // put your setup code here, to run once:
  for (int i=start_pin; i < start_pin+count_pins; i++) {
    pinMode(i, OUTPUT);
  }
  Serial.begin(2000000);
}

void solo_acentos(int _delay){
  bool _scene[count_pins];
  for (int i1=0; i1 < count_pins-1; i1++) {
    _scene[i1] = false;
  }
  _scene[7]=true;
  _scene[14]=true;
  _scene[0]=true;
  print_scene(_scene,_delay);
}

int current_scene = 12;
int veces;
int scenas = 12;

void loop() {
  Serial.println(current_scene);
  veces = random(1,5);
  for (int i=0; i < veces; i++) {
    switch (current_scene) {
      case 1:
        scene_1();
        break;
      case 2:
        scene_2();
        break;
      case 3:
        scene_3();
        break;
      case 4:
        strobo(random(25,100));
        break;
      case 5:
        vibra(100,25);
        break;
      case 6:
        al_centro_y_vuelta(50);
        break;
      case 7:
        al_centro(random(25,200));
        break;
      case 8:
        para_afuera(random(25,200));
        break;
      case 9:
        cosa_1(random(25,200));
      case 10:
        silencio(random(1000,5000));
      case 11:
        pleno(random(1000,5000));
      case 12:
        solo_acentos(random(1000,5000));
    }
  }
  current_scene = random(0,scenas);
}
