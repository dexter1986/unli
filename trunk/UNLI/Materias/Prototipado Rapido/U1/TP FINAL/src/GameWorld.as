package
{
	import adobe.utils.CustomActions;
	import net.flashpunk.Entity;
	import net.flashpunk.graphics.Image;
	import net.flashpunk.FP;
	import net.flashpunk.masks.Pixelmask;
	import net.flashpunk.utils.Key;
	import net.flashpunk.utils.Input;
	import net.flashpunk.World;
	import net.flashpunk.tweens.misc.VarTween;
	import net.flashpunk.utils.Ease;
	import net.flashpunk.graphics.Text;
	
	public class GameWorld extends World
	{	
		public function GameWorld()
		{		
		}
		
		private function resetGame():void
   	    {     
		    FP.world = new GameWorld();           
		}
		
		private function endLevel():void
        {
			/*
               //Reset counter
               endLevelCounter = 0;               
               removeAll();               
               if (currentLevel == 1)
               {
                    trace("LEVEL ONE ENDING");                    
                    currentLevel++;                    
                    //Load level 2
                    getTheLevel();
               }
               else if (currentLevel == 2)
               {
                    trace("LEVEL TWO ENDING");                                                                                
                    currentLevel++;                    
                    //Load level 3
                    getTheLevel();
               }
               else if (currentLevel == 3)
               {
                    trace("LEVEL THREE ENDING");                    
                    //Game end
                    endGame();
               }
			   */
          }
		  
		  private function getTheLevel():void
          {
			  /*
               FP.camera.y = CAMERA_START;               
               
               //Replace HUD pieces that were removed on level end
               add(new HUD);
               add(new HUDTwo);
               add(new HUDTwoText(this));
               
               spawnType = 1;
               warlord = null;
               
               handCursorRef = new HandCursor(this);
               add(handCursorRef);
               
               var dataList:XMLList;
               var dataElement:XML;
               
               var loadLevel:Level;
               
               trace("Loading level " + currentLevel);
               
               //Select which level to load
               if (currentLevel == 1) { loadLevel = Level(add(new Level(LEVEL_01))); }
               else if (currentLevel == 2) { loadLevel = Level(add(new Level(LEVEL_02))); }
               else if (currentLevel == 3) { loadLevel = Level(add(new Level(LEVEL_03))); }
              
               
               //Begin transition screen
               if (currentLevel == 1) { add(new LevelTransition(1, this)); }
               else if (currentLevel == 2) { add(new LevelTransition(2, this)); }
               else if (currentLevel == 3) { add(new LevelTransition(3, this)); }
          
               levelTransitioning = true;
			   */
          }
		  
		  private function gameOver():void
          {
			  /*
               if (gameIsFinished == false)
               {
                    trace("You lose!");
                    //removeAll();
                    GameIsFinished = true;
                    DEFEAT.play(.75);
                    BGM.stop();
                    add(gameOverScreen);
                    gameOverBeingDisplayed = true;
               }
			   */
          }
		  
		  private function endGame():void
          {
			  /*
               //Win game here
               add(gameWinScreen);
               add(gameWinText);
               
               //A conditional here would be ideal to determine if the player qualifies for inputting a high score:
               add(initials);
               add(initHeader);
               
               TURN_OFF_HUD_SELECTING = true;
               
               
               // INITIALS CODE HERE JUST NEED A VARIABLE to pass to setVariable
               
               
               // Sets the user intials in the database from the text input
               Main.myDBComm.setVariable("userInitials", "AAA", Main.mainUserID);
               
               BGM.stop();
               VICTORY.play(.75);
               
               gameOverBeingDisplayed = true;
			   */
        }
		
		public function InitGame():void 
		{
			
		}
		
		public function NextLevel():void 
		{
			//_nextlevel = true;
		}	
		
		override public function update():void
		{
			if (Input.pressed(Key.SPACE))
			{
				this.active = false;
			}
			super.update();
		}
	}
}