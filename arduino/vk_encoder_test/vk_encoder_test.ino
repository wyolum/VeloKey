// program feather M0 but select Arduino Zero in Board menu

#define ncodr Serial1
// #define SerialDBG SerialUSB
#define SerialDBG SERIAL_PORT_USBVIRTUAL

union Data{
  int16_t value;
  char bytes[3];
};

Data enca_u;
Data encb_u;

void setup(void) {
  SerialDBG.begin(9600);
  SerialDBG.println("HERE!!!");
  ncodr.begin(57600);
  ncodr.write('a'); // zero out encoder a
  delay(1);
  ncodr.write('b'); // zero out encoder b
}

void loop() {
  readEncoder();
  SerialDBG.print(enca_u.value);
  SerialDBG.print(" ");
  SerialDBG.println(encb_u.value);
  delay(100);
}

bool readEncoder(){
  //read encoder value into global enca_u.value
  bool out = false;
  ncodr.print("R");
  if(ncodr.available()){
    out = true;
    enca_u.bytes[0] = ncodr.read(); // receive a byte as character
    enca_u.bytes[1] = ncodr.read(); // receive a byte as character
    enca_u.bytes[2] = ncodr.read(); // receive a byte as character
    encb_u.bytes[0] = ncodr.read(); // receive a byte as character
    encb_u.bytes[1] = ncodr.read(); // receive a byte as character
    encb_u.bytes[2] = ncodr.read(); // receive a byte as character
    while(ncodr.available()){
      ncodr.read();
    }
  }
  return out;
}
