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
	import net.flashpunk.Graphic;
	import net.flashpunk.graphics.Image;
	/**
	 * ...
	 * @author Oscar Sanchez
	 */
	public class Inicio extends World 
	{
		
		[Embed(source="../assets/gfx/FondoIntro.png")]
		private const IMG:Class;
		public var image:Image;	
		
		
		protected var titleText:Text;		
		protected var clicText:Text;
		private var fadeTween:VarTween;
		private var fadeTween2:VarTween;
		private var _Level:int = 0;
		private var status:String = "";
		
		public function Inicio() 
		{
			CreateLevel();
		}
		
		public function CreateLevel():void
		{
			this.titleText = new Text("----------------------------------------------------------------------\n----------------------------------------------------------------------\n----------------------------------------------------------------------\n");						
			this.titleText.color = 0xFFFFFF;
			this.titleText.scale = 1.5;			
			this.titleText.alpha = 1;
			
			this.titleText.x = (FP.screen.width - this.titleText.scaledWidth) / 2;
						
			this.titleText.y = 100;
						
			this.clicText = new Text("Haz clic para continuar");
			this.clicText.color = 0xFFFFFF;
			this.clicText.x = (FP.screen.width - this.clicText.width) / 2;
			this.clicText.y = FP.screen.height * 0.85;
			this.clicText.alpha = 0;
			
			fadeTween = new VarTween();	
			fadeTween2= new VarTween();	
			
			image = new Image(IMG);			
			this.addGraphic(image);
			
			this.addGraphic(titleText);
			this.addGraphic(clicText);
			
			this.addTween(fadeTween);	
			this.addTween(fadeTween2);
		}	
		
		override public function begin():void
		{
			_Level = 0;		
			status = "FIRST";
			titleText.text = "";
			this.clicText.alpha = 0;
			this.titleText.alpha = 1;
			this.image.alpha = 0;
		}
		
		override public function update():void
		{
			switch (status)
			{
				case "FIRST":
				{
					fadeTween.tween(image, "alpha", 1, 1);
					this.status = "FADEBACKGROUND";
					break;
				}
				case "FADEBACKGROUND":
				{
					if (fadeTween.percent == 1)
					{
						this.status = "NEXT";
					}
					break
				}
				case "NEXT": 
				{
					this.status = "FADEOUT";					
					break;
				}	
				case "FADEOUT":
				{
					fadeTween.tween(titleText, "alpha", 0, 1);
					fadeTween2.tween(clicText, "alpha", 0, 1);
					this.status = "WAITFADE";
					break;
				}
				
				case "FADEIN":
				{
					fadeTween.tween(titleText, "alpha", 1, 1);
					fadeTween2.tween(clicText, "alpha", 1, 1);
					this.status = "WAITFADELOAD";
					break;
				}
				
				case "WAITFADE": 
				{
					if (fadeTween.percent == 1)
					{
						this.status = "LOAD";						
					}
					break;
				}
				
				case "WAITFADELOAD":
				{
					if (fadeTween.percent == 1)
					{
						this.status = "READY";
					}
					break
				}
				
				case "LOAD":
				{
					LoadLevel();
					this.status = "FADEIN";
					break;
				}
				
				case "READY":
				{
					if (Input.mousePressed)
					{
						NextLevel();
						this.status = "NEXT";
					}
					break;
				}
			}
			super.update();			
		}
	
		function NextLevel():void 
		{
			_Level = _Level + 1;
		}
		
		function LoadLevel():void 	
		{
			switch (_Level) 
			{
			case 0:
				titleText.text = "Algunas Religiones creen que en el momento de nacer nuestro\nespiritu es asignado a un cuerpo";				
				break;
			case 1:
				titleText.text = "Algunas creencias dicen que al morir vemos un especie\nde tunel";
				break;
			case 2:
				titleText.text = "Nadie puede saber si esto es real hasta que llega\nsu momento";
				break;
			case 3:
				titleText.text = "Puede que esto tenga algo de razon y\neste relacionado con nuestro comportamiento\nal cabo de nuestra vida";
				break;
			case 4:
				titleText.text = "Lo que si sabemos es que al momento\nde nacer o partir estamos solos";
				break;
			case 5:
				titleText.text = "            ¿PREPARADO PARA UNA NUEVA AVENTURA?";
				break;
				default:
				 this.active = false;
			}
		}
		
	}
}