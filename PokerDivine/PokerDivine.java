import java.awt.* ;
import java.awt.event.* ;
import javax.swing.* ;

public class PokerDivine {
	public static void main(String[] args) {
		Poker poker = new Poker() ;
		
		GameGUI game = new GameGUI(poker) ;
		poker.initial() ;
	}
}