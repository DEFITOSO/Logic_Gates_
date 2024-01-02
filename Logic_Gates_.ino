// Initial parameters and weights
int th = 3;
int wnot = 1;
int wand1 = 1;
int wand2 = 1;
int wor1 = 3;
int wor2 = 3;
int wxor1 = 1;
int wxor2 = 1;
int bias = 1;
int lr = 1;
int w[] = {0.5, 0.5, 0.5};

int or_percep(int in1, int in2){
    int result = in1 * wor1 + in2 * wor2;
    if (result >= 3) {
      return HIGH;
    } else {
      return LOW;
    }
} 

int and_percep(int in1, int in2){
  int result = in1 * wand1 + in2 * wand2;
  if (result >= 2) {
    return HIGH;
  } else {
    return LOW;
  }
} 

int not_percep(int in1){
  int result = in1 * wnot;
  if (result >= 1) {
    return LOW;
  } else {
    return HIGH;
  }
}

int xor_percep(int in1, int in2){
    return and_percep(not_percep(and_percep(in1, in2)), or_percep(in1,in2));
}

int tr_neuron(int in1,int in2, int real,int lr){
  int calc = in1*w[0] + in2*w[1] + bias*w[2];
  if (calc >= 0){
    calc = 1;
  } else{
    calc = 0;
  }
  int err = real - calc;
  w[0] = w[0] + err*in1*lr;
  w[1] = w[1] + err*in2*lr;
  w[2] = w[2] + err*bias*lr;
}

int or_train(int epochs){
  for (int i = 0; i < epochs; i++){
    tr_neuron(0,0,0,lr);
    tr_neuron(1,1,1,lr);
    tr_neuron(1,0,1,lr);
    tr_neuron(0,1,1,lr);
  }
}

int and_train(int epochs){
  for (int i = 0; i < epochs; i++){
    tr_neuron(0,0,0,lr);
    tr_neuron(1,1,1,lr);
    tr_neuron(1,0,0,lr);
    tr_neuron(0,1,0,lr);
  }
}

int or_trpercep(int in1, int in2, int b){
    int result = in1 * w[0] + in2 * w[1] + b * w[2];
    if (result >= 0) {
      return HIGH;
    } else {
      return LOW;
    }
} 

int and_trpercep(int in1, int in2, int b){
    int result = in1 * w[0] + in2 * w[1] + b * w[2];
    if (result >= 0) {
      return HIGH;
    } else {
      return LOW;
    }
} 

void setup() {
  pinMode(4, OUTPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
}

void loop() {
  int sel = 4;
  int ss0= digitalRead(9);
  int ss1= digitalRead(10);
  int output;

  if (sel == 1){
    output = or_percep(ss0, ss1);
  } 
  else if (sel == 2){
    output = and_percep(ss0, ss1);
  }
  else if (sel == 3){
    output = xor_percep(ss0, ss1);
  } else if (sel == 4){
    or_train(250);
    output = or_trpercep(ss0,ss1,bias);
  } else if (sel == 5) {
    and_train(250);
    output = and_trpercep(ss0,ss1,bias);
  }
   
  digitalWrite(4,output);
  
}