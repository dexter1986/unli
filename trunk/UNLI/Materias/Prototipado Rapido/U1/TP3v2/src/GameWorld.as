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
		private var player:Player;
		private var simTri:Simbolo;
		private var simOnda:Simbolo;
		private var simOjo:Simbolo;
		private var simCirc:Simbolo;
		private var simEst:Simbolo;
		
		public var RestartGame:Boolean = false;
		public var _nextlevel:Boolean = false;
				
		public function GameWorld()
		{
			CreateMenu();
			
			InitGame();
			
			gameReboot();			
		}
		
		public function CreateMenu():void
		{
			this.titleText = new Text("TP 3");
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
			simTri = new Simbolo(FP.screen.width / 4, FP.screen.height / 4);			
			simTri.Setup("triangulo", 0x00FFFFFF, false);						
			this.add(simTri);
			simOnda = new Simbolo(FP.screen.width - FP.screen.width / 4, FP.screen.height / 4);
			simOnda.Setup("onda", 0x00FFFFFF, false);		
			this.add(simOnda);			
			simCirc = new Simbolo(FP.screen.width / 4, FP.screen.height - FP.screen.height / 4);
			simCirc.Setup("circulo", 0x00FFFFFF, false);
			this.add(simCirc);
			simEst = new Simbolo(FP.screen.width - FP.screen.width / 4, FP.screen.height - FP.screen.height / 4);
			simEst.Setup("estrella",0x00FFFFFF,false);			
			this.add(simEst);
			simOjo = new Simbolo(FP.screen.width / 2, FP.screen.height / 2);
			simOjo.Setup("ojo", 0x00FFFFFF, true);
			this.add(simOjo);
			player = new Player(0, 0);			
			this.add(player);
			player.Setup(FP.screen.width / 2 - player.width / 2, FP.screen.height -  FP.screen.height / 4);
		}
		
		public function NewGame():void 
		{		
			RestartGame = false;
			//-->	
			SetEntitiesColors();
			
			simCirc.visible = true;
			simEst.visible = true;			
			simOnda.visible = true;
			simTri.visible = true;			
			simOjo.visible = true;
		}
		
		private function SetEntitiesColors():void 
		{			
			/*
			var colorR1:uint = 0xFF0000;
			var colorG1:uint = 0x00FF00;			
			var colorB1:uint = 0x0000FF;
			*/
			
			var colorWhite:uint = 0xFFFFFF;
			
			var aux:int = 255;
			var auxColor:uint;
			
			var colorR:uint = colorWhite;
			var colorG:uint = colorWhite;
			var colorB:uint = colorWhite;			
			var colorAux:uint = colorWhite;
			
			aux = FP.rand(206) + 50;
			colorB = aux;			
			aux = FP.rand(206) + 50;
			colorG = aux << 8;
			aux = FP.rand(206) + 50;
			colorR = aux << 16;						
				
				switch (FP.rand(4))
				{
					case 0:
						simCirc.Init(colorG);
						simEst.Init(colorR);
						simOnda.Init(colorB);
						simTri.Init(colorWhite);
					break;
					case 1:
						simCirc.Init(colorWhite);
						simEst.Init(colorG);
						simOnda.Init(colorR);
						simTri.Init(colorB);
					break;
					case 2:
						simCirc.Init(colorB);
						simEst.Init(colorWhite);
						simOnda.Init(colorG);
						simTri.Init(colorR);
					break;
					case 3:
						simCirc.Init(colorR);
						simEst.Init(colorB);
						simOnda.Init(colorWhite);
						simTri.Init(colorG);
					break;
					default:
				}
				

			switch (FP.rand(3))
			{
				case 0:
					colorAux = colorR | colorG;
				break;
				case 1:
					colorAux = colorR | colorB;
				break;
				case 2:
					colorAux = colorB | colorG;
				break;				
				default:
			}
			
			simOjo.Init(colorAux);				
			player.Init(colorWhite);
		}
		
		public function NextLevel():void 
		{
			_nextlevel = true;
		}
		
		public function gameReboot():void
		{
			RestartGame = false;
			this.status = "START";				
			//this.status = "GAME";	
			Reboot();
		}		
		
		public function Reboot():void
		{
			simCirc.visible = false;
			simEst.visible = false;
			simOjo.visible = false;
			simOnda.visible = false;
			simTri.visible = false;
			player.visible = false;
			player.isDead = false;
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
				
				case "WAIT1":
				{
					if (titleTweenIn.percent == 1 && pressTweenIn.percent == 1)
					{
						this.status = "TO";
					}
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
				
				case "WAIT2":
				{
					if (titleTweenOut.percent == 1 && pressTweenOut.percent == 1)
					{				
						this.status = "GAME";
						NewGame();
					}					
				}
				
				case "GAME": 
				{					
					if (RestartGame)
					{
						gameReboot();
					}
					
					if (_nextlevel)
					{
						_nextlevel = false;
						Reboot();
						NewGame();
					}
				}
			}
			
			
			
			super.update();
		}
	}
}