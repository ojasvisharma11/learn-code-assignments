import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;
import java.math.BigInteger; 
import java.security.MessageDigest; 
import java.security.NoSuchAlgorithmException; 

//---- Do not change the code.....//
class  Counter{

    int count = 0; 
    long threadId = 999999;
     
     void  add(){
         if(threadId != Thread.currentThread().getId()){
              threadId = Thread.currentThread().getId(); 
          }else{
               System.out.println("Error : Same thread id cannot proceed");
              return;
          }
         
     	for (int i = 0; i < 100000; i++) {
		   count++;
		 
     	}
        try{
		     Thread.sleep(1); 
		 }catch(Exception e){
		     
		 }
    }
    
    int getTotalCount(){
        return count;
    }
}
class  MyThread implements Runnable{
    private Counter increment;
    public MyThread(Counter incr){
        this.increment = incr;
    }
    public void run(){
        this.increment.add();
    }
    public int getTotalCount(){
        return this.increment.getTotalCount();
    }
}

public class Solution {

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int intiger = scan.nextInt();
      	Counter counter = new Counter();
        
        int no_of_times = intiger/100000;
        MyThread myIncrement = new MyThread(counter);
        Thread increment[] = new Thread[no_of_times];
        for(int i=0;i<no_of_times;i++){
            increment[i] = new Thread(myIncrement);
            increment[i].start();
            try{
                increment[i].join();
            }
            catch(Exception e){}
        }
       
           //  Solution is the main Class. Please write your code here, you can also create new classes. 
          //Hint : 1. Use counter object in line no 46  and span threads that will call the counter.add() method                   internally. 
          //       2. Wait for all threads to finish.
          //       learn to create Threads in Java : https://www.javatpoint.com/creating-thread
               
      
      
      
      
      //dont not change this code; this is for output
      System.out.println(counter.getTotalCount());
      
    }
}
