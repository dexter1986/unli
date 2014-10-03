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
		protected var titleText:Text;
		protected var pressText:Text;
		private var titleTweenIn:VarTween;
		private var titleTweenOut:VarTween;
		private var pressTweenIn:VarTween;
		private var pressTweenOut:VarTween;
		protected var status:String;
	
		
		[Embed(source="Background.png")]
		private const BACK_IMG:Class;
		private var backImg:Image
		
		private var player:Player;
		
		public function GameWorld()
		{
			CreateMenu();
			
			InitGame();
			
			gameReboot();			
		}
		
		public function CreateMenu():void
		{
			this.titleText = new Text("TP 5");
			this.pressText = new Text("Press SPACE BAR to start");
			
			this.titleText.color = 0xFFFFFF;
			this.titleText.scale = 2;
			this.pressText.color = 0xFFFFFF;
			this.pressText.alpha = 0;
			
			this.titleText.x = (FP.screen.width - this.titleText.scaledWidth) / 2;
			this.pressText.x = (FP.screen.width - this.pressText.width) / 2;
			
			this.titleText.y = -100;
			this.pressText.y = FP.screen.height * 0.75;
			
			titleTweenIn = new VarTween();
			titleTweenOut = new VarTween();
			pressTweenIn = new VarTween();
			pressTweenOut = new VarTween();
			
			this.addGraphic(titleText);
			this.addGraphic(pressText);
			
			this.addTween(titleTweenIn);
			this.addTween(pressTweenIn);
			this.addTween(titleTweenOut);
			this.addTween(pressTweenOut);
		}
		
		public function InitGame():void 
		{
			//-->
			backImg = new Image(BACK_IMG);
			this.addGraphic(backImg);
			player = new Player(FP.screen.width / 2, FP.screen.height / 2);
			this.add(player);
		}
		
		public function NewGame():void 
		{		
			//-->
			backImg.alpha = 1;
			this.player.visible = true;
			this.player.playerImage.visible = true;
			this.player.collidable = true;			
		}
		
		public function gameReboot():void
		{
			this.status = "START";
			//-->	
			backImg.alpha = 0;
			this.player.visible = false;
			this.player.collidable = false;			
			this.player.playerImage.play("idle");
			this.player.isDead = false;
		}
		
		override public function update():void
		{
			switch (status)
			{
				case "START": 
				{
					titleTweenIn.tween(titleText, "y", FP.screen.height * 0.25, 1, Ease.backOut);
					pressTweenIn.tween(pressText, "alpha", 1, 1);
					
					this.status = "WAIT1";
					break;
				}
				
				case "TO": 
				{
					if (Input.check(Key.SPACE))
					{
						titleTweenOut.tween(titleText, "y", -100, 1, Ease.backIn);
						pressTweenOut.tween(pressText, "alpha", 0, 1);
						this.status = "WAIT2";
					}
					break;
				}
				
				case "GAME": 
				{					
					if (classCount(Player) == 0)
					{
						gameReboot();
					}
					
					if (classCount(Enemigo) < 3)
					{	
						var e:Enemigo = new Enemigo(FP.screen.width - (FP.rand(200) + 100) , FP.screen.height / 2);
						this.add(e);						
					}
					
				}
			}
			
			if (titleTweenIn.percent == 1 && pressTweenIn.percent == 1 && this.status == "WAIT1")
				this.status = "TO";
			
			if (titleTweenOut.percent == 1 && pressTweenOut.percent == 1 && this.status == "WAIT2")
			{				
				this.status = "GAME";		
				NewGame();	
			}
			
			super.update();
		}
	}
}