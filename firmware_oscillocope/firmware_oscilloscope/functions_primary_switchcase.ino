void Settings(int*response,int size){
  switch (size){
    case 15 : ReInitParams(response,size);break;
    case 5 : FiveParamsFun(response,size);break;
    case 3 : ThreeParamsFun(response,size);break;
    case 2 : TwoParamsFun(response,size);break;
    case 1 : ReadNewData();break;
  }
}

void ReInitParams(int*resp,int count){
  
  ADJ_HORIZONTAL = resp[0];
  TIMEBASE_INDEX = resp[1];
  
  ADJ_VERTICAL = resp[2];
  CHANNEL_1 = resp[3];
  ch1.amplitude_index = resp[4];
  
  ADJ_VERTICAL = resp[5];
  CHANNEL_2 = resp[6];
  ch2.amplitude_index = resp[7];

  ADJ_POSITION = resp[8];
  CHANNEL_1 = resp[9];
  ch1.position = resp[10];

  ADJ_POSITION = resp[11];
  CHANNEL_2 = resp[12];
  ch2.position = resp[13];

  REQ_DATA = resp[14];

  Log("MESSAGE","INIT SUCCESS");
    
}

void FiveParamsFun(int*resp,int count){
  
  ADJ_VERTICAL = resp[0];
  
  CHANNEL_1 = resp[1];
  ch1.amplitude_index = resp[2];
  
  CHANNEL_2 = resp[3];
  ch2.amplitude_index = resp[4];

  Log("INFO","AMPLITUDE INDEX OF BOTH CHANNELS UPDATED");
  
}

void ThreeParamsFun(int*resp,int count){
  
  // If the first parameter is a ADJ_VERTICAL, then the below two funtions are invoked, depending on the second index of the array
  if(ADJ_VERTICAL == resp[0] && CHANNEL_1 == resp[1]){
    ADJ_VERTICAL = resp[0];
    CHANNEL_1 = resp[1];
    ch1.amplitude_index = resp[2];
    Log("INFO","CHANNEL 1 AMPLITUDE INDEX UPDATED");
  }
  if(ADJ_VERTICAL == resp[0] && CHANNEL_2 == resp[1]){
    ADJ_VERTICAL = resp[0];
    CHANNEL_2 = resp[1];
    ch2.amplitude_index = resp[2];
    Log("INFO","CHANNEL 2 AMPLITUDE INDEX UPDATED");
  }
  
  // If the first parameter is a ADJ_POSITION, then the below two funtions are invoked, depending on the second index of the array
  if(ADJ_POSITION == resp[0] && CHANNEL_1 == resp[1]){
    ADJ_POSITION = resp[0];
    CHANNEL_1 = resp[1];
    ch1.position = resp[2];
    Log("INFO","CHANNEL 1 POSITION UPDATED");
  }
  if(ADJ_POSITION == resp[0] && CHANNEL_2 == resp[1]){
    ADJ_POSITION = resp[0];
    CHANNEL_2 = resp[1];
    ch2.position = resp[2];
    Log("INFO","CHANNEL 2 POSITION UPDATED");
  }

}

void TwoParamsFun(int*resp,int count){
  
  // This updates the timebase index of both the channels
  ADJ_HORIZONTAL = resp[0];
  TIMEBASE_INDEX = resp[1];
  ch1.timebase_index = ch2.timebase_index = TIMEBASE_INDEX;
  Log("INFO","TIMEBASE INDEX UPDATED FOR BOTH CHANNELS");

}

int LenOfDataFromAndroid(int*resp){
  // This function also updates the obtained data to the response array
  //The array is referenced with address of the main array using pointers.
  int count = 0;
  bool condition = false;
  while(android.available()){
    delay(1);
    int temp_response = android.read();
    resp[count] = temp_response;
    condition = true;
    count++;
  }
  return condition?count:-1;
}
