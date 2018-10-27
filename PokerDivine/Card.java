public class Card {
	public static final String[] patternName = {"Club" , "Diamond" , "Heart" , "Spade"} ;
	
	public int number ;
	public String pattern ;
	
	public Card (String pattern , int number) {
		this.number = number;
		this.pattern = pattern;
	}
	
	public int getNumber () {
		return number ;
	}
	
	public String getPattern () {
		return pattern ;
	}
	
	public int getPosition () {
		int patternNumber=0;
		for (int i=0; i<4; i++) {
			if (this.pattern == this.patternName[i]) {
				patternNumber = i;
			}
		}
		return (patternNumber*10 + (this.number-1));
	}
	
	public void showCard () {
		System.out.print (this.pattern.charAt(0) + Integer.toString(this.number) + " ") ;
	}
}