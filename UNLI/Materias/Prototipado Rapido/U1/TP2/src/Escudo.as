package   
{
	import adobe.utils.CustomActions;
	import flash.display.BitmapData;
	import flash.geom.Rectangle;
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
	
	/**
	 * ...
	 * @author ...
	 */
	public class Escudo extends Entity 
	{
		[Embed(source="escudo.png")]
		private const IMG :Class;		
			
		[Embed(source="escudo.png")]
		private const SPRITE :Class;
		private var sprite:Spritemap;
		
		private var grp_List:Graphiclist;
		private var posX:int;
		private var posY:int;
		private var velRot:int = 300;
		private var velLentoRot:int = 10;
		private var centX:Number;
		private var centY:Number;
		private var ang:Number;
		private var collrect:Rectangle = new Rectangle();
		public function Escudo(px:Number=0, py:Number=0) 
		{
			sprite = new Spritemap(SPRITE, 100, 100);			
			sprite.add("idle", [0,1,2,3,4,5,6,7,8,9], 30, true);

			grp_List = new Graphiclist(sprite);	

			super(px, py, grp_List);			
			
			type = "Escudo";				
			sprite.play("idle");
		}
		
		public function Init():void 
		{
			x += getWidth() - 20 ;			
			y -= getHeight() / 2;		
			
			sprite.originX = 0;
			sprite.originY = getHeight();
			sprite.alpha = 0.8;						
			posX = 0;
			posY = 0;
			centX = FP.screen.width / 2;
			centY = FP.screen.height / 2;
		}
		
		public function getWidth():Number
		{
			return (sprite.width / sprite.columns);
		}
		
		public function getHeight():Number
		{
			return (sprite.height / sprite.rows);
		}		
		
		private function CheckCollition():void
		{
			var balas:Array = [];
			world.getClass(Bala, balas);
			
			for each (var e:Bala in balas)
			{
				if (!e.isDead)
				{
					if (collrect.contains(e.x, e.y))
					{
						e.die();
					}
				}
			}
		}
		
		private function  UpdateCollitionRect():void 
		{
			co
		}
		
		override public function update():void 
		{
			if (posX != Input.mouseX || posY != Input.mouseY)
			{
				posX = Input.mouseX - centX;
				posY = Input.mouseY - centY;
				
				if (posY < 0)
				{
					ang = Math.atan(posX / posY) * 180 / 3.14 + 45;
					sprite.angle = 	ang;					
				}
				else 
				{
					ang = 180 + Math.atan(posX / posY) * 180 / 3.14 + 45;
					sprite.angle = ang;									
				}
			}
			
			posX = Input.mouseX;
			posY = Input.mouseY;			
			
			CheckCollition();
			
			super.update();
		}
		
	}
}