import java.io.* ;
import java.awt.* ;
import javax.swing.* ;
import java.awt.event.*;
import java.lang.*;

public class GameGUI {
	private Poker poker ;
	
	private JFrame gameFrame ;
	public WindowPane window;
	
	public GameGUI(Poker poker) {
		this.poker = poker ;
		this.poker.setGameGUI (this) ;
		
		gameFrame = new JFrame("PokerDivine") ;
		gameFrame.setSize(1366 , 726) ;
		gameFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE) ;
	
		window = new WindowPane() ;
		gameFrame.add(window) ;
		
		gameFrame.setVisible(true) ;
	}
	
	public class WindowPane extends JLayeredPane {
		private ImageIcon background_ImageIcon ;
		
		public JButton start_Button;
		public JLabel onegame_handCardNumber_Label;
		public JLabel onegame_totalUsedCardNumber_Label;
		public JLabel totalgame_win_Label;
		public JLabel totalgame_winAverageCard_Label;
		public JLabel totalgame_lose_Label;
		public JLabel totalgame_loseAverageCard_Label;
		public JLabel totalgame_successRate_Label;
		
		public JTextField times;
		
		public JLabel[] cardsLabel;
		public ImageIcon[] originCardsImageIcon;
		public ImageIcon[] cardsImageIcon ;
		public ImageIcon backImageIcon ;
		
		private int timePeriod;
		
		public WindowPane() {
			this.setLayout(null) ;
			background_ImageIcon = new ImageIcon("./images/table.jpg") ;
			
			start_Button = new JButton ("Start");
			start_Button.setBounds (125, 580, 80, 20);
			start_Button.addMouseListener(new start_Button_MouseListener());
			this.add(start_Button);
			
			times = new JTextField("1");
			times.setBounds (125, 550, 80, 20);
			this.add(times);
			
			onegame_handCardNumber_Label = new JLabel("Hand : 40");
			onegame_handCardNumber_Label.setFont(new Font("TimesNewRoman", Font.BOLD, 22));
			onegame_handCardNumber_Label.setForeground (Color.green);
			onegame_handCardNumber_Label.setBounds (1150, 90, 220, 30);
			this.add(onegame_handCardNumber_Label);
			
			onegame_totalUsedCardNumber_Label = new JLabel("UsedCard : 0.0");
			onegame_totalUsedCardNumber_Label.setFont(new Font("TimesNewRoman", Font.BOLD, 22));
			onegame_totalUsedCardNumber_Label.setForeground (Color.white);
			onegame_totalUsedCardNumber_Label.setBounds (1150, 40, 220, 30);
			this.add(onegame_totalUsedCardNumber_Label);
			
			totalgame_win_Label = new JLabel("Win : 0");
			totalgame_win_Label.setFont(new Font("TimesNewRoman", Font.BOLD, 22));
			totalgame_win_Label.setForeground (Color.pink);
			totalgame_win_Label.setBounds (50, 40, 350, 30);
			this.add(totalgame_win_Label);
			
			totalgame_winAverageCard_Label = new JLabel("Average Used : 0.00");
			totalgame_winAverageCard_Label.setFont(new Font("TimesNewRoman", Font.BOLD, 22));
			totalgame_winAverageCard_Label.setForeground (Color.pink);
			totalgame_winAverageCard_Label.setBounds (50, 70, 350, 30);
			this.add(totalgame_winAverageCard_Label);
			
			totalgame_lose_Label = new JLabel("Lose : 0");
			totalgame_lose_Label.setFont(new Font("TimesNewRoman", Font.BOLD, 22));
			totalgame_lose_Label.setForeground (Color.lightGray);
			totalgame_lose_Label.setBounds (50, 120, 350, 30);
			this.add(totalgame_lose_Label);
			
			totalgame_loseAverageCard_Label = new JLabel("Average Used : 0.00");
			totalgame_loseAverageCard_Label.setFont(new Font("TimesNewRoman", Font.BOLD, 22));
			totalgame_loseAverageCard_Label.setForeground (Color.lightGray);
			totalgame_loseAverageCard_Label.setBounds (50, 150, 350, 30);
			this.add(totalgame_loseAverageCard_Label);
			
			totalgame_successRate_Label = new JLabel("Success Rate : 0.00 %");
			totalgame_successRate_Label.setFont(new Font("TimesNewRoman", Font.BOLD, 22));
			totalgame_successRate_Label.setForeground (Color.yellow);
			totalgame_successRate_Label.setBounds (50, 250, 350, 30);
			this.add(totalgame_successRate_Label);
			
			backImageIcon = new ImageIcon ("./images/cardBack2.jpg");
			cardsLabel = new JLabel[40];
			originCardsImageIcon = new ImageIcon[40];
			cardsImageIcon = new ImageIcon[40];
			for (int i=0; i<40; i++) {
				originCardsImageIcon[i] = new ImageIcon("./images/"+ Card.patternName[i/10].charAt(0) + Integer.toString(i%10+1) + ".png");
				cardsImageIcon[i] = new ImageIcon();
				cardsLabel[i] = new JLabel() ;
				cardsLabel[i].setVisible (true) ;
				this.add(cardsLabel[i]) ;
			}
			this.timePeriod = 0;
		}
		public void paintComponent(Graphics g) {
			super.paintComponent(g) ;
			background_ImageIcon.paintIcon(this , g , 0 , 0) ;
			
			if (poker.moveFlag) {
				Point nowPosition = new Point() ;
				nowPosition = cardsLabel[poker.cardsQueue[poker.nowCard]].getLocation() ;
				nowPosition.translate(1*(int)Math.signum(poker.stackPosition[poker.stackIndex]-nowPosition.getX()) , 1*(int)Math.signum(15+15*poker.stackCardNumber[poker.stackIndex]-nowPosition.getY())) ; 
				this.cardsLabel[poker.cardsQueue[poker.nowCard]].setLocation (nowPosition) ;
				
				if (nowPosition.getX() == poker.stackPosition[poker.stackIndex] && nowPosition.getY() == 15+15*poker.stackCardNumber[poker.stackIndex]) {
					poker.nextDeal();
				}
				
				timePeriod = (timePeriod+1)%1000;
				if (timePeriod == 0) {
					try {
					Thread.sleep(1);
					}
					catch (Exception e) {
						System.out.println(e);
					}
				}
			}
		}
		
		public class start_Button_MouseListener extends MouseAdapter  {
			public void mousePressed (MouseEvent e) {
				start_Button.setVisible (false);
				times.setVisible (false);
				
				poker.totalgame_win = 0;
				poker.totalgame_winTotalCard = 0;
				poker.totalgame_lose = 0;
				poker.totalgame_loseTotalCard = 0;
				
				totalgame_win_Label.setText("Win : 0");
				totalgame_winAverageCard_Label.setText("Average Used : 0.00");
				totalgame_lose_Label.setText("Lose : 0");
				totalgame_loseAverageCard_Label.setText("Average Used : 0.00");
				totalgame_win_Label.setText("Success Rate : 0.00 %");
				
				poker.loopGame();
			}
		}
	}
}

