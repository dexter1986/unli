package   
{
	import adobe.utils.CustomActions;
	import flash.display.BitmapData;
	import flash.geom.Rectangle;
	import flash.geom.Transform;
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
	import net.flashpunk.utils.Draw;
	
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
			var oldAng:Number = -(sprite.angle) * 3.14 / 180;
			
			var dx:Number = x + sprite.originX;
			var dy:Number = y + sprite.originY;
			
			var l:Number = 100;		
			
			var tx:Number = dx + Math.cos(oldAng-3.14/4) * l;
			var ty:Number = dy + Math.sin(oldAng-3.14/4) * l;
			
			var tx1:Number = dx + Math.cos(oldAng) * l;
			var ty1:Number = dy + Math.sin(oldAng) * l;
			
			var tx2:Number = dx + Math.cos(oldAng-3.14/2) * l;
			var ty2:Number = dy + Math.sin(oldAng-3.14/2) * l;
			
			
			
			var balas:Array = [];
			world.getClass(Bala, balas);
			
			for each (var e:Bala in balas)
			{
				if (!e.isDead)
				{
					/*
					if (collrect.contains(e.x, e.y))
					{
						e.die();
					}
					*/					
				}
			}
		}
		
		override public function render():void 
		{
			var oldAng:Number = -(sprite.angle) * 3.14 / 180;
			
			var dx:Number = x + sprite.originX;
			var dy:Number = y + sprite.originY;
			
			var l:Number = 100;		
			
			var tx:Number = dx + Math.cos(oldAng-3.14/4) * l;
			var ty:Number = dy + Math.sin(oldAng-3.14/4) * l;
			
			var tx1:Number = dx + Math.cos(oldAng) * l;
			var ty1:Number = dy + Math.sin(oldAng) * l;
			
			var tx2:Number = dx + Math.cos(oldAng-3.14/2) * l;
			var ty2:Number = dy + Math.sin(oldAng-3.14/2) * l;
				
			
			
			//+45
			Draw.line(dx, dy, tx1, ty1, 0xff0000);						
			
			//medio
			Draw.line(dx,dy,tx,ty,0xff0000);
			
			//-45
			Draw.line(dx, dy, tx2, ty2, 0xff0000);
			
			Draw.line(tx1, ty1, tx, ty, 0xff0000);
			
			Draw.line(tx, ty, tx2, ty2, 0xff0000);	
			
			Draw.line(tx1,ty1,tx2,ty2,0xff0000);	
			
			super.render();
		}
		
		override public function update():void 
		{	
			if (posX != Input.mouseX || posY != Input.mouseY)
			{
				posX = centX - Input.mouseX;
				posY = centY - Input.mouseY;
				
				if (posY < 0 )
				{
					sprite.angle = (Math.atan(posX / posY) + 3.14 / 4) * 180 / 3.14;// + 45;
				}
				else 
				{
					sprite.angle =  (Math.atan(posX / posY) + 3.14 + 3.14 / 4) * 180 / 3.14; 
				}
			}
			
			posX = Input.mouseX;
			posY = Input.mouseY
			
			CheckCollition();
			
			super.update();
		}
		
	}
}