package
{
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
		var fondoUp:Este;
		var fondoDo:Esul;
		
		public function GameWorld()
		{
			this.titleText = new Text("TP 4");
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
			
			
			fondoUp = new Este(0, 0);
			fondoDo = new Esul(0, FP.screen.height - 100);
			
			this.add(fondoUp);
			this.add(fondoDo);		
			
			gameReboot();
			
			//FP.console.enable();
		}
		
		public function NewGame():void 
		{
			FP.screen.color = 0xffffff;			
			this.add(new Globo(100, 230));			
			this.add(new Globo(FP.screen.width /2 - 120, 230));
			this.add(new Globo(FP.screen.width / 2  + 70, 230));
			this.add(new Globo(FP.screen.width - 150, 230));				
			fondoDo.visible = true;
			fondoUp.visible = true;
		}
		
		public function gameReboot():void
		{
			FP.screen.color = 0x000000;	
			fondoDo.visible = false;
			fondoUp.visible = false;
			this.status = "START";
		}
		
		override public function update():void
		{
			switch (status)
			{
				case "START": 
				{
					titleTweenIn.tween(titleText, "y", FP.screen.height * 0.25, 3, Ease.backOut);
					pressTweenIn.tween(pressText, "alpha", 1, 3);
					
					this.status = "WAIT1";
					break;
				}
				
				case "TO": 
				{
					if (Input.check(Key.SPACE))
					{
						titleTweenOut.tween(titleText, "y", -100, 3, Ease.backIn);
						pressTweenOut.tween(pressText, "alpha", 0, 3);
						this.status = "WAIT2";
					}
					break;
				}
				
				case "GAME": 
				{
					//Game
					if (classCount(Globo) == 0)
					{
						gameReboot();
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