import java.io.*;
import java.lang.*;
public class Bank{
	private int balance=1000;

	public static void main(String args[]) throws Exception{
		BufferedReader console = new BufferedReader(new InputStreamReader(System.in));   
		Bank bank= new Bank();
	
		bank.balance = Integer.parseInt(console.readLine());
      
		DepositThread deposit=new DepositThread(bank);
		WithdrawThread withdraw = new WithdrawThread(bank);
        synchronized(bank){
            deposit.start();
            deposit.join();
        }
		synchronized(bank){
            withdraw.start();
            withdraw.join();
        }
		System.out.println("all done: balance = "+bank.balance);

	}
	public void deposit(){
		for(int i=0;i<1e7;i++){
			balance++;
        }
	}
	public void withdraw(){
		for(int i=0;i<1e7;i++){
			balance--;
		}
	}
}

class DepositThread extends Thread{
	Bank bank;
	DepositThread(Bank bank){
		this.bank = bank;
	}
	public void run(){
		bank.deposit();
	}
}
class WithdrawThread extends Thread{
	Bank bank;
	WithdrawThread(Bank bank){
		this.bank = bank;
	}

	public void run(){
		bank.withdraw();
	}
}
