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
	
	/**
	 * ...
	 * @author ...
	 */
	public class Simbolo extends Entity 
	{		
		[Embed(source="textura.png")]
		private const IMG:Class;
		private var sprite:Spritemap;
		
		private var grp_List:Graphiclist;
		private var  scale:Number = 0.5;
		private var IsTheKey:Boolean = false;
		
				
		public function Simbolo(px:Number = 0, py:Number = 0) 
		{	
			sprite = new Spritemap(IMG, 128, 127);	
			
			sprite.scale = scale;
			
			sprite.add("triangulo", [0], 1, false);
			sprite.add("onda", [1], 1, false);
			sprite.add("ojo", [2], 1, false);
			sprite.add("circulo", [3], 1, false);
			sprite.add("estrella", [4], 1, false);
			
			setHitbox(128*scale, 128*scale);
			width = 128
			height = 128;
			
			grp_List = new Graphiclist(sprite);
			
			super(px-width/2, py-height/2, grp_List);
			
			type = "Simbolo";
			
			sprite.play("idle");				
		}
		
		public function Setup(simbolo:String,color:uint,isKey:Boolean):void 
		{
			sprite.color = color;			
			sprite.play(simbolo);
			IsTheKey = isKey;
		}
		
		public function Init(color:uint):void 
		{
			sprite.color = color;						
		}
		
		public function GetColor():uint
		{
			return sprite.color;
		}
		
		public function  IsKey():Boolean
		{
			return IsTheKey;
		}
		
		override public function update():void
		{				
		}
		
		public function  die():void 
		{				
		}
		
	}
}
