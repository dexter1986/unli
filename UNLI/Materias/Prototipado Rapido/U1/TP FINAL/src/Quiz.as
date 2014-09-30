package  
{
	import adobe.utils.CustomActions;
	import flash.display.BitmapData;
	import flash.sampler.NewObjectSample;
	import net.flashpunk.Entity;
	import net.flashpunk.Graphic;
	import net.flashpunk.graphics.Image;
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
		
		private  var sprite:Spritemap;	
		private var grp_List:Graphiclist;
		private var scale:Number = 1;
		private var  description:String;
				
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
			
			setHitbox(96*scale, 96*scale);
			width = 96;
			height = 96;
						
			grp_List = new Graphiclist(sprite);	
			
			super(px, py, grp_List);				
			
			type = "quiz";				
		}
		
		public function Initialize():void 
		{
			sprite.play("iglesia");
		}
		
		public function GetRandQuiz(edad:int, ispareja:Boolean = false,ishijo:Boolean=false):void 
		{
			if (edad < 5)
			{
				
			}
			else if (edad < 15)
			{
				
			}
			else if(edad < 25)
			{
				
			}
			else if(edad < 65)
			{
				
			}
			else
			{
				
			}
		}
				
		public function GetDescription():String 
		{
			return description;
		}
		
		override public function update():void
		{
			super.update();
		}		
	}
}