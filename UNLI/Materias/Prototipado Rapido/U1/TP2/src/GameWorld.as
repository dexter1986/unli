package
{
	import net.flashpunk.graphics.Text;
	import net.flashpunk.World;
	import net.flashpunk.FP;
	import net.flashpunk.tweens.misc.VarTween;
	import net.flashpunk.utils.Ease;
	import net.flashpunk.utils.Input;
	import net.flashpunk.utils.Key;
	
	public class GameWorld extends World
	{
		protected var titleText:Text;
		protected var pressText:Text;
		private var titleTweenIn:VarTween;
		private var titleTweenOut:VarTween;
		private var pressTweenIn:VarTween;
		private var pressTweenOut:VarTween;
		protected var status:String;
		
		
		private var corazon:Corazon;
		private var escudo:Escudo;
		private var background:Background;
		
		public function GameWorld()
		{			
			this.titleText = new Text("TP2");
			this.pressText = new Text("Press SPACE BAR to start");
			
			this.titleText.color = 0xFF0000;
			this.titleText.scale = 2;
			this.pressText.color = 0x00FF00;
			this.pressText.alpha = 0;
			
			this.titleText.x = (FP.screen.width - this.titleText.scaledWidth) / 2;
			this.pressText.x = (FP.screen.width - this.pressText.width) / 2;
			
			this.titleText.y = -100;
			this.pressText.y = FP.screen.height * 0.75;
			
			titleTweenIn = new VarTween();
			titleTweenOut = new VarTween();
			pressTweenIn = new VarTween();
			pressTweenOut = new VarTween();
			
			this.status = "START";			
			
			this.addGraphic(titleText);
			this.addGraphic(pressText);
			
			this.addTween(titleTweenIn);
			this.addTween(pressTweenIn);
			this.addTween(titleTweenOut);
			this.addTween(pressTweenOut);
			
			this.background = new Background();
			this.add(background);
			
			this.corazon = new Corazon(FP.screen.width / 2, FP.screen.height / 2);
			this.corazon.x = FP.screen.width / 2 - this.corazon.getWidth() / 2;
			this.corazon.y = FP.screen.height / 2 - this.corazon.getHeight() / 2;
			this.add(corazon);
			
			this.escudo = new Escudo(FP.screen.width / 2, FP.screen.height / 2);
			this.escudo.x = FP.screen.width / 2 - this.escudo.img.width / 2;
			this.escudo.y = FP.screen.height / 2 - this.escudo.img.height / 2;
			this.escudo.Init();
			this.add(escudo);	
			
			gameReboot();
		}
		
		private var wait:Number;		
		private var ang:Number;	
		private var iterCount:int = 0;
		
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
					if (!corazon.isDead)
					{
						wait -= FP.elapsed;
						
						if (wait <= 0)
						{
							NormalFire();						
							wait = FP.rand(1) + 1;	
							iterCount++;
						}			
					}					
				}
			}
			
			if (titleTweenIn.percent == 1 && pressTweenIn.percent == 1 && this.status == "WAIT1")
				this.status = "TO";
			
			if (titleTweenOut.percent == 1 && pressTweenOut.percent == 1 && this.status == "WAIT2")
			{
				StartGame();
			}
			
			super.update();						
		}
		
		private function  StartGame():void 
		{
			this.corazon.visible = true;
			this.corazon.collidable = true;				
			this.escudo.visible = true;
			this.escudo.collidable = true;
			this.status = "GAME";
		}
		
		private function  NormalFire():void 
		{
			var max:int = FP.rand(3)+1;
			for (var i:int = 0; i < max; i++) 
			{
				ang = FP.rand(4);
				switch (ang) 
				{
					case 0:	
						Fire(0);
					break;	
					case 1:		
						Fire(90);
					break;	
					case 2:		
						Fire(180);
					break;	
					case 3:			
						Fire(270);
					break;	
				}
			}
		}
		
		private function  PatternFire():void 
		{
			ang = FP.rand(4);
			switch (ang) 
			{
				case 0:	
					Fire(0);				
				case 1:		
					Fire(90);				
				case 2:		
					Fire(180);				
				case 3:			
					Fire(270);				
			}
		}
		
		private var bala:Bala;
		
		private function Fire(ang:int):void 
		{
			if (classCount(Bala) < 30)
			{
				bala = new Bala(200 + FP.rand(400),100 + FP.rand(400));					
				bala.Init(ang);
				this.add(bala);				
			}
		}
		
		public function gameReboot():void
		{
			this.corazon.visible = false;
			this.corazon.collidable = false;
			this.corazon.sprite.visible = true;
			this.corazon.sprite.play("idle");
			this.corazon.isDead = false;			
			this.escudo.visible = false;
			this.escudo.collidable = false;
			
			this.status = "START";
			
			wait = FP.rand(1) + 1;
			iterCount = 0;
			
		
		}
	}
}