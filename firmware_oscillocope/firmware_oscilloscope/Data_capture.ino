void ReadNewData(){
  Log("CHECK","READING...");
  int i = 0;
  while(!(android.available())){
    if(i<MAX_SAMPLES){
      if(i%2==0){
        android.write(analogRead(A0)*5/1023);
      }
      else{
        android.write(analogRead(A1)*5/1023);
      }
      i++;
    }
  }
}
