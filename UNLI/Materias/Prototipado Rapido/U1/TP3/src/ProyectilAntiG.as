package  
{
	import net.flashpunk.Entity;	
	import net.flashpunk.Graphic;
	import net.flashpunk.graphics.Spritemap;
	import net.flashpunk.Mask;
	import net.flashpunk.utils.Input;
	import net.flashpunk.utils.Key;
	import net.flashpunk.FP;
	
	/**
	 * ...
	 * @author ...
	 */
	public class Proyectil extends Proyectil 
	{
		[Embed(source = "bala.png")]
		private const BALA_IMG:Class;
		
		private var balaImg:Spritemap;
		
		private const SCALE = 0.5;
		private const VEL_X = 500;
		
		private var dir_x = 0;
		
		public function Proyectil(x:Number=0, y:Number=0,dir:Number=1) 
		{
			balaImg = new Spritemap(BALA_IMG, 32, 32);
			
			balaImg.scale = SCALE;
			
			balaImg.add("fire", [0, 1, 2, 3, 4, 5], 20, true);			
					
			setHitbox(32 * SCALE, 32 * SCALE);
			
			width = 32;
			height = 32;
			
			balaImg.play("fire");
			balaImg.smooth = true;
			
			dir_x = dir;
			
			var posx = x;
			
			/*
			if (dir > 0)
			{
				posx = x + 100 * dir * SCALE;
			}
			*/
			
			super(x, y, balaImg);	
			
			type = "ProyectilAntiG";
		}
		
		override public function update():void 
		{	
			x += VEL_X * dir_x * FP.elapsed;
			
			if (x > FP.screen.width || x < 0)
			{
				this.destroy();
			}			
			
			var b = collide("Enemigo", x, y) as Enemigo;
			if (b)
			{
				if (!b.isAntiGEffect)
				{
					destroy();
					b.activaAnti_g();				
				}
			}	
			
			super.update();
		}
				
		public function destroy():void
		{			
			FP.world.remove(this);
		}		
	}

}