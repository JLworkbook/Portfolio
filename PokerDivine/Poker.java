import java.util.* ;
import java.awt.* ;
import javax.swing.* ;
import java.lang.*;

public class Poker {
	private Card[] cards ;
	private GameGUI gui ;
	
	public int[] stackPosition;
	public int[] stackCardNumber;
	public int[][] stackContent;
	public int stackNumber;
	public int stackIndex;
	
	public int[] cardsQueue;
	public int nowCard, backCard;
	public int backUpNumber;
	public boolean moveFlag, firstRunFlag;
	
	public int onegame_handCardNumber;
	public int onegame_totalUsedCardNumber;
	public int totalgame_win;
	public int totalgame_winTotalCard;
	public int totalgame_lose;
	public int totalgame_loseTotalCard;
	
	public Poker () {
		this.cards = new Card[40];
		
		for (int i=0 ; i<4 ; i++) {
			for (int j=0 ; j<10 ; j++) {
				this.cards[i*10+j] = new Card(Card.patternName[i] , j+1) ;
			}
		}
		
		this.stackPosition = new int[4];
		this.stackCardNumber = new int[4];
		this.stackContent = new int[4][40];
		
		this.cardsQueue = new int[40];
		this.moveFlag = false;
		
		this.totalgame_win = 0;
		this.totalgame_winTotalCard = 0;
		this.totalgame_lose = 0;
		this.totalgame_loseTotalCard = 0;
	}
	
	public void setGameGUI (GameGUI gui) {
		this.gui = gui ;
	}
	
	public void initial () {
		shuffle() ;
		
		for (int i=0; i<40; i++) {
			gui.window.cardsImageIcon[i].setImage(gui.window.originCardsImageIcon[cards[i].getPosition()].getImage());
			gui.window.cardsLabel[i].setIcon (gui.window.backImageIcon) ;
			gui.window.cardsLabel[i].setBounds (644-(i/3) , 510+(i/3) , 80 , 123) ;
			gui.window.setLayer (gui.window.cardsLabel[i] , 80-i) ;
			
			cardsQueue[i] = i;
		}
		nowCard = 0;
		backCard = 0;
		backUpNumber = 0;
		
		for (int i=0; i<4; i++) {
			this.stackPosition[i] = 250+150*(i+1);
		}
		for (int i=0; i<4; i++) {
			this.stackCardNumber[i] = 0;
		}
		
		this.stackNumber = 4;
		this.stackIndex = 0;
		this.moveFlag = false;
		this.firstRunFlag = true;
		
		this.onegame_totalUsedCardNumber = 0;
		this.onegame_handCardNumber = 40;
		
		gui.window.onegame_totalUsedCardNumber_Label.setText ("UsedCard : 0");
		gui.window.onegame_handCardNumber_Label.setText ("Hand : 40");
	}
	
	private void shuffle () {
		Random ran = new Random() ;
       
		for (int i=this.cards.length ; i>1 ; i--) {
			swap (this.cards , i-1 , ran.nextInt(i)) ;
		}
	}
	
	private void swap (Card[] cards , int i , int j) {
		Card temp = cards[i] ;
		cards[i] = cards[j] ;
		cards[j] = temp ;
	}
	
	public void showAllCard () {
		for (int i=0 ; i<cards.length ; i++) {
			cards[i].showCard() ;
		}
		System.out.println() ;
	}
	
	public Card[] getCards () {
		return cards ;
	}
	
	public void loopGame() {
		try {
			int targetGameNumber = Integer.parseInt(gui.window.times.getText());
			if ((totalgame_win + totalgame_lose) < targetGameNumber)
				startGame();
			else {
				gui.window.start_Button.setVisible (true);
				gui.window.times.setVisible (true);
			}
		}
		catch (NumberFormatException e) {
			System.out.println (e);
			gui.window.start_Button.setVisible (true);
			gui.window.times.setVisible (true);
		}
	}
	
	public void startGame () {
		initial ();
		
		gui.window.cardsLabel[cardsQueue[nowCard]].setIcon (gui.window.cardsImageIcon[cardsQueue[nowCard]]);
		
		moveFlag = true;
		gui.window.repaint();
	}
	
	private void checkReceive() {
		int[] sum = new int[3];
		if (stackCardNumber[stackIndex] > 3) {
			sum[0] = cards[stackContent[stackIndex][0]].number + cards[stackContent[stackIndex][1]].number + cards[stackContent[stackIndex][stackCardNumber[stackIndex]-1]].number;
			sum[1] = cards[stackContent[stackIndex][0]].number + cards[stackContent[stackIndex][stackCardNumber[stackIndex]-1]].number + cards[stackContent[stackIndex][stackCardNumber[stackIndex]-2]].number;
			sum[2] = cards[stackContent[stackIndex][stackCardNumber[stackIndex]-1]].number + cards[stackContent[stackIndex][stackCardNumber[stackIndex]-2]].number + cards[stackContent[stackIndex][stackCardNumber[stackIndex]-3]].number;
			
			if (sum[0]%10 == 9) {
				gui.window.cardsLabel[stackContent[stackIndex][stackCardNumber[stackIndex]-1]].setLocation(1200, 360);
				gui.window.cardsLabel[stackContent[stackIndex][0]].setLocation(1200, 380);
				gui.window.cardsLabel[stackContent[stackIndex][1]].setLocation(1200, 400);
				
				cardsQueue[(backCard+backUpNumber+0)%40] = stackContent[stackIndex][stackCardNumber[stackIndex]-1];
				cardsQueue[(backCard+backUpNumber+1)%40] = stackContent[stackIndex][0];
				cardsQueue[(backCard+backUpNumber+2)%40] = stackContent[stackIndex][1];
				
				gui.window.setLayer (gui.window.cardsLabel[stackContent[stackIndex][stackCardNumber[stackIndex]-1]], backUpNumber++);
				gui.window.setLayer (gui.window.cardsLabel[stackContent[stackIndex][0]], backUpNumber++);
				gui.window.setLayer (gui.window.cardsLabel[stackContent[stackIndex][1]], backUpNumber++);
				
				for (int i=2; i<stackCardNumber[stackIndex]-1; i++) {
					gui.window.cardsLabel[stackContent[stackIndex][i]].setLocation(gui.window.cardsLabel[stackContent[stackIndex][i]].getX(), gui.window.cardsLabel[stackContent[stackIndex][i]].getY() - 15*2);
					gui.window.setLayer (gui.window.cardsLabel[stackContent[stackIndex][i]], i-2);
					stackContent[stackIndex][i-2] = stackContent[stackIndex][i];
				}
				stackCardNumber[stackIndex] -= 3;
				onegame_handCardNumber += 3;
			}
			else if (sum[1]%10 == 9) {
				gui.window.cardsLabel[stackContent[stackIndex][stackCardNumber[stackIndex]-2]].setLocation(1200, 360);
				gui.window.cardsLabel[stackContent[stackIndex][stackCardNumber[stackIndex]-1]].setLocation(1200, 380);
				gui.window.cardsLabel[stackContent[stackIndex][0]].setLocation(1200, 400);
				
				cardsQueue[(backCard+backUpNumber+0)%40] = stackContent[stackIndex][stackCardNumber[stackIndex]-2];
				cardsQueue[(backCard+backUpNumber+1)%40] = stackContent[stackIndex][stackCardNumber[stackIndex]-1];
				cardsQueue[(backCard+backUpNumber+2)%40] = stackContent[stackIndex][0];
				
				gui.window.setLayer (gui.window.cardsLabel[stackContent[stackIndex][stackCardNumber[stackIndex]-2]], backUpNumber++);
				gui.window.setLayer (gui.window.cardsLabel[stackContent[stackIndex][stackCardNumber[stackIndex]-1]], backUpNumber++);
				gui.window.setLayer (gui.window.cardsLabel[stackContent[stackIndex][0]], backUpNumber++);
				
				for (int i=1; i<stackCardNumber[stackIndex]-2; i++) {
					gui.window.cardsLabel[stackContent[stackIndex][i]].setLocation(gui.window.cardsLabel[stackContent[stackIndex][i]].getX(), gui.window.cardsLabel[stackContent[stackIndex][i]].getY() - 15*1);
					gui.window.setLayer (gui.window.cardsLabel[stackContent[stackIndex][i]], i-1);
					stackContent[stackIndex][i-1] = stackContent[stackIndex][i];
				}
				stackCardNumber[stackIndex] -= 3;
				onegame_handCardNumber += 3;
			}
			else if (sum[2]%10 == 9) {
				gui.window.cardsLabel[stackContent[stackIndex][stackCardNumber[stackIndex]-3]].setLocation(1200, 360);
				gui.window.cardsLabel[stackContent[stackIndex][stackCardNumber[stackIndex]-2]].setLocation(1200, 380);
				gui.window.cardsLabel[stackContent[stackIndex][stackCardNumber[stackIndex]-1]].setLocation(1200, 400);
				
				cardsQueue[(backCard+backUpNumber+0)%40] = stackContent[stackIndex][stackCardNumber[stackIndex]-3];
				cardsQueue[(backCard+backUpNumber+1)%40] = stackContent[stackIndex][stackCardNumber[stackIndex]-2];
				cardsQueue[(backCard+backUpNumber+2)%40] = stackContent[stackIndex][stackCardNumber[stackIndex]-1];
				
				gui.window.setLayer (gui.window.cardsLabel[stackContent[stackIndex][stackCardNumber[stackIndex]-3]], backUpNumber++);
				gui.window.setLayer (gui.window.cardsLabel[stackContent[stackIndex][stackCardNumber[stackIndex]-2]], backUpNumber++);
				gui.window.setLayer (gui.window.cardsLabel[stackContent[stackIndex][stackCardNumber[stackIndex]-1]], backUpNumber++);
				
				stackCardNumber[stackIndex] -= 3;
				onegame_handCardNumber += 3;
			}
		}
		else if (stackCardNumber[stackIndex] == 3) {
			if (stackNumber != 1) {
				sum[0] = cards[stackContent[stackIndex][0]].number + cards[stackContent[stackIndex][1]].number + cards[stackContent[stackIndex][2]].number;
				if (sum[0]%10 == 9) {
					gui.window.cardsLabel[stackContent[stackIndex][0]].setLocation(1200, 360);
					gui.window.cardsLabel[stackContent[stackIndex][1]].setLocation(1200, 380);
					gui.window.cardsLabel[stackContent[stackIndex][2]].setLocation(1200, 400);
					
					cardsQueue[(backCard+backUpNumber+0)%40] = stackContent[stackIndex][0];
					cardsQueue[(backCard+backUpNumber+1)%40] = stackContent[stackIndex][1];
					cardsQueue[(backCard+backUpNumber+2)%40] = stackContent[stackIndex][2];
					
					gui.window.setLayer (gui.window.cardsLabel[stackContent[stackIndex][0]], backUpNumber++);
					gui.window.setLayer (gui.window.cardsLabel[stackContent[stackIndex][1]], backUpNumber++);
					gui.window.setLayer (gui.window.cardsLabel[stackContent[stackIndex][2]], backUpNumber++);
					
					stackCardNumber[stackIndex] -= 3;
					onegame_handCardNumber += 3;
					
					for (int i=stackIndex+1; i<4; i++) {
						for (int j=0; j<stackCardNumber[i]; j++) {
							stackContent[i-1][j] = stackContent[i][j];
						}
						stackCardNumber[i-1] = stackCardNumber[i];
						stackPosition[i-1] = stackPosition[i];
					}
					stackNumber--;
					stackIndex--;
				}
			}
			else {
				sum[0] = cards[stackContent[stackIndex][0]].number + cards[stackContent[stackIndex][1]].number + cards[stackContent[stackIndex][2]].number;
				if (sum[0]%10 == 9) {
					gui.window.cardsLabel[stackContent[stackIndex][0]].setLocation(1200, 360);
					gui.window.cardsLabel[stackContent[stackIndex][1]].setLocation(1200, 380);
					gui.window.cardsLabel[stackContent[stackIndex][2]].setLocation(1200, 400);
					
					cardsQueue[(backCard+backUpNumber+0)%40] = stackContent[stackIndex][0];
					cardsQueue[(backCard+backUpNumber+1)%40] = stackContent[stackIndex][1];
					cardsQueue[(backCard+backUpNumber+2)%40] = stackContent[stackIndex][2];
					
					gui.window.setLayer (gui.window.cardsLabel[stackContent[stackIndex][0]], backUpNumber++);
					gui.window.setLayer (gui.window.cardsLabel[stackContent[stackIndex][1]], backUpNumber++);
					gui.window.setLayer (gui.window.cardsLabel[stackContent[stackIndex][2]], backUpNumber++);
					
					stackCardNumber[stackIndex] -= 3;
					onegame_handCardNumber += 3;
				}
			}
		}
	}
	
	private boolean checkFinish () {
		if (stackNumber == 1 && stackCardNumber[0] == 1 && (!firstRunFlag) && cards[stackContent[0][0]].number == 3)
			return true;
		else
			return false;
	}
	
	public void nextDeal () {
		gui.window.setLayer (gui.window.cardsLabel[cardsQueue[nowCard]] , stackCardNumber[stackIndex]) ;
		
		stackContent[stackIndex][stackCardNumber[stackIndex]] = cardsQueue[nowCard];
		stackCardNumber[stackIndex]++;
		
		onegame_totalUsedCardNumber++;
		onegame_handCardNumber--;
		if (onegame_totalUsedCardNumber > 2000) {
			totalgame_lose++;
			totalgame_loseTotalCard += onegame_totalUsedCardNumber;
			gui.window.totalgame_lose_Label.setText ("Lose : " + Integer.toString(totalgame_lose));
			gui.window.totalgame_loseAverageCard_Label.setText ("Average Used : " + String.format("%.2f", (double)totalgame_loseTotalCard/(double)totalgame_lose));
			gui.window.totalgame_successRate_Label.setText ("Success Rate : " + String.format("%.2f", 100.0*(double)totalgame_win/(double)(totalgame_win+totalgame_lose) ) + " %");
			
			moveFlag = false;
			loopGame ();
			
			return;
		}
		
		
		checkReceive ();
		gui.window.onegame_totalUsedCardNumber_Label.setText ("UsedCard : " + Integer.toString(onegame_totalUsedCardNumber));
		gui.window.onegame_handCardNumber_Label.setText ("Hand : " + Integer.toString(onegame_handCardNumber));
		
		if (checkFinish ()) {
			totalgame_win++;
			totalgame_winTotalCard += onegame_totalUsedCardNumber;
			gui.window.totalgame_win_Label.setText ("Win : " + Integer.toString(totalgame_win));
			gui.window.totalgame_winAverageCard_Label.setText ("Average Used : " + String.format("%.2f", (double)totalgame_winTotalCard/(double)totalgame_win));
			gui.window.totalgame_successRate_Label.setText ("Success Rate : " + String.format("%.2f", 100.0*(double)totalgame_win/(double)(totalgame_win+totalgame_lose) ) + " %");
			
			moveFlag = false;
			loopGame ();
			//gui.window.start_Button.setVisible (true);
			return;
		}
		
		nowCard = (nowCard+1)%40;
		stackIndex = (stackIndex+1)%stackNumber;
		
		if (nowCard == backCard) {
			int i, j;
			
			if (backUpNumber == 0) {
				totalgame_lose++;
				totalgame_loseTotalCard += onegame_totalUsedCardNumber;
				gui.window.totalgame_lose_Label.setText ("Lose : " + Integer.toString(totalgame_lose));
				gui.window.totalgame_loseAverageCard_Label.setText ("Average Used : " + String.format("%.2f", (double)totalgame_loseTotalCard/(double)totalgame_lose));
				gui.window.totalgame_successRate_Label.setText ("Success Rate : " + String.format("%.2f", 100.0*(double)totalgame_win/(double)(totalgame_win+totalgame_lose) ) + " %");
				
				moveFlag = false;
				loopGame ();
				//gui.window.start_Button.setVisible (true);
				return;
			}
			else {
				firstRunFlag = false;
				backCard = (backCard+backUpNumber)%40;
				backUpNumber = 0;
				if (nowCard > backCard) {
					for (i=nowCard, j=0; i<40; i++, j++) {
						gui.window.cardsLabel[cardsQueue[i]].setLocation (644-(j/3) , 510+(j/3));
						gui.window.setLayer (gui.window.cardsLabel[cardsQueue[i]], 80-j);
						gui.window.cardsLabel[cardsQueue[i]].setIcon (gui.window.backImageIcon) ;
					}
					for (i=0, j=j; i<backCard; i++, j++) {
						gui.window.cardsLabel[cardsQueue[i]].setLocation (644-(j/3) , 510+(j/3));
						gui.window.setLayer (gui.window.cardsLabel[cardsQueue[i]], 80-j);
						gui.window.cardsLabel[cardsQueue[i]].setIcon (gui.window.backImageIcon) ;
					}
				}
				else {
					for (i=nowCard, j=0; i<backCard; i++, j++) {
						gui.window.cardsLabel[cardsQueue[i]].setLocation (644-(j/3) , 510+(j/3));
						gui.window.setLayer (gui.window.cardsLabel[cardsQueue[i]], 80-j);
						gui.window.cardsLabel[cardsQueue[i]].setIcon (gui.window.backImageIcon) ;
					}
				}
			}
		}
		
		gui.window.cardsLabel[cardsQueue[nowCard]].setIcon (gui.window.cardsImageIcon[cardsQueue[nowCard]]);
	}
}