package  
{
	import adobe.utils.CustomActions;
	import flash.display.BitmapData;
	import flash.display.Graphics;
	import flash.sampler.NewObjectSample;
	import flash.text.engine.TextBlock;
	import net.flashpunk.Entity;
	import net.flashpunk.Graphic;
	import net.flashpunk.graphics.Image;
	import net.flashpunk.graphics.Text;
	import net.flashpunk.masks.Pixelmask;
	import net.flashpunk.Sfx;
	import net.flashpunk.graphics.Emitter;
	import net.flashpunk.graphics.Graphiclist;
	import net.flashpunk.graphics.Spritemap;
	import net.flashpunk.utils.Key;
	import net.flashpunk.utils.Input;
	import net.flashpunk.FP;
	import net.flashpunk.Tween;
	import net.flashpunk.utils.Ease;
	import net.flashpunk.tweens.misc.VarTween;
	import net.flashpunk.utils.Ease;
	import net.flashpunk.tweens.misc.MultiVarTween;
	
	/**
	 * ...
	 * @author Oscar Sanchez
	 */
	public class Quiz extends Entity 
	{
		[Embed(source="../assets/gfx/Iconos.png")]
		private const IMG:Class;
		
		private var sprite:Spritemap;	
		private var grp_List:Graphiclist;
		private var scale:Number = 1;
		private var description:String;		
		private var IsOk:Boolean;
		private var Tipo:int;		
		private var _OnClick:Boolean;
		
		public function Quiz(px:Number = 0, py:Number = 0) 
		{			
			sprite = new Spritemap(IMG,64,64);
			sprite.add("iglesia",[0], 1, false);			
			sprite.add("diversion", [1], 1, false);
			sprite.add("cena", [2], 1, false);
			sprite.add("jugarhijos", [3], 1, false);
			sprite.add("amor", [4], 1, false);
			sprite.add("dinero", [5], 1, false);
			sprite.add("trabajar", [6], 1, false);
			sprite.add("cruz", [7], 1, false);
			sprite.add("boca", [8], 1, false);
			sprite.add("jugar", [9], 1, false);
			
			sprite.scale = scale;
			
			setHitbox(128*scale, 128*scale);
			width = 128;
			height = 128;
			
			grp_List = new Graphiclist();	
			grp_List.add(sprite);
									
			super(px, py, grp_List);				
			
			type = "quiz";	
		}
		
		public function Initialize():void 
		{
			sprite.visible = false;		
			IsOk = false;
			Tipo = -1;
		}
		
		public function GetRandQuiz(edad:int,ispareja:Boolean = false,ishijo:Boolean=false):void 
		{
			IsOk = false;
			Tipo = -1;
			_OnClick = false
			
			if (edad < 5)
			{
				Tipo = 9;
			}
			else if (edad < 10)
			{
				if (FP.rand(8) > 4)
				{
					Tipo = 0;
				}
				else
				{
					Tipo = 9;
				}
			}
			else if (edad < 65)
			{	
				var aux:int = FP.rand(10);
				if (aux > 0 && aux < 5)
				{
					aux = FP.rand(25);
					if (aux > 0 && aux < 5)
					{
						Tipo = 0;		
					}
					else if (aux > 5 && aux < 10)
					{
						Tipo = 1;
					}
					else if (!ispareja && aux > 10 && aux < 20)
					{
						Tipo = 4;
					}
					else if (aux > 20 && aux < 25)
					{
						Tipo = 5;
					}
				}
				
				if (ispareja)
				{
					aux = FP.rand(20)
					if ( aux > 0 && aux < 5)
					{
						Tipo = 2;				
					}
					else if (aux > 5 && aux < 10)
					{
						Tipo = 4;
					}
					else if(aux > 10 && aux < 15)
					{
						Tipo = 8;
					}
				}
				
				if (ishijo)
				{
					aux = FP.rand(5);
					if (aux > 3)
					{
						Tipo = 3;
					}
				}
			}
			else if (edad > 65)
			{
				var aux:int = FP.rand(8);
				Tipo = 0;
				Tipo = 1;
				
				if (aux > 0 && aux < 5)
				{
					aux = FP.rand(15);
					if (aux > 0 && aux < 5)
					{
						Tipo = 0;		
					}
					else if (aux > 5 && aux < 10)
					{
						Tipo = 1;
					}
					else if (aux > 10 && aux < 15)
					{
						Tipo = 5;
					}
				}
				if (ispareja)
				{
					aux = FP.rand(10)
					if ( aux > 0 && aux < 5)
					{
						Tipo = 2;				
					}
				}				
			}
						
			switch (Tipo) 
			{
				case 0:
					description = "Puede ser un buen momento\npara cultivar tu Fe?";
					sprite.play("iglesia");	
				break;
				case 1:
					description = "Creo que tengo que darme\nel tiempo para divertirme y \nconocer gente?";
					sprite.play("diversion");					
				break;
				case 2:
					description = "Deberia prestar mas atencion\na mi familia?";
					sprite.play("cena");
				break;
				case 3:
					description = "Deberia dedicar un poco de\nmi tiempo para jugar con\nmis hijos?";
					sprite.play("jugarhijos");
				break;
				case 4:
					description = "Sera este el momento\npara enamorarme?";
					sprite.play("amor");
				break;
				case 5:
					description = "Ser caritativo o no ser\nes la cuestion?";
					sprite.play("dinero");
				break;
				case 6:
					description = "Otro dia mas y\nla rutina llama para cumplir\nmis obligaciones\?";
					sprite.play("trabajar");
				break;
				case 7:
					description = "Hay momentos en los cuales\nsuceden profundos cambios";
					sprite.play("cruz");
				break;
				case 8:
					description = "Ser fiel o infiel\nes la cuestion?";
					sprite.play("boca");
				break;
				case 9:
					if (edad < 10)
					{
						description = "Dicen que jugar ayuda a crecer?";
					}
					else
					{
						description = "Dicen que jugar ayuda a crecer\npero el estudio tambien?";
					}
					sprite.play("jugar");
				break;
				default:					
				break;
			}			
		}
		
		public function  GetResult():Boolean 
		{
			return IsOk;
		}
		
		public function GetTipo():int 
		{
			return Tipo;
		}
		
		public function  SetShow(value:Boolean):void 
		{
			sprite.visible = value;
		}
		
		public function OnClick():Boolean 
		{
			return _OnClick;
		}
				
		public function GetDescription():String 
		{
			return description;
		}
		
		override public function update():void
		{
			if (Input.mousePressed)
			{
				_OnClick = true;
				
				if (collidePoint(x, y, Input.mouseX, Input.mouseY))
				{
					IsOk = true;					
				}
				
			}
			super.update();
		}		
	}
}