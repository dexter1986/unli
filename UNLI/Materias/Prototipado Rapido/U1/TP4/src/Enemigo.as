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
	public class Enemigo extends Entity 
	{
		[Embed(source="soldado.png")]
		private const ENEMIGO_IMG:Class;
		
		private var enemigoImg:Spritemap;
		
		private const SCALE = 1.0;
		private const VEL_X = 200;
		private const VEL_X_anti_g = 50;
		private const VEL_Y = 300;
		private const VEL_Y_JUMP = 200;
		private const DIR_L = -1;
		private const DIR_R = 1;				
		private const DIR_NA = 0;
		private const GRAVEDAD = -500;
		private const FRICCION = 500;
		private const MAX_anti_g = 3.5;
		
		private const PISO_Y = 400;
		
		private var dir_x_f = 0;
		private var dir_x = 0;		
		private var vel_x = 0;
		private var vel_y = 0;
		private var anti_g = false;		
		private var center_y = 0;
		private var angulo = 0;		
		private var anti_g_carga = 0.0;
		private var isAnti_g_cargado = true;
		
		public function Enemigo(x:Number=0, y:Number=0, graphic:Graphic=null, mask:Mask=null) 
		{
			enemigoImg = new Spritemap(ENEMIGO_IMG,34, 44);
			
			enemigoImg.add("idle", [0], 10, true);
			enemigoImg.add("run",[1,2,3,4,5], 20, true);
			
			setHitbox(33*SCALE, 44*SCALE);
			
			width = 33;
			height = 44;
			
			enemigoImg.smooth = true;
			enemigoImg.scale = SCALE;
			
			enemigoImg.play("idle");
			
			super(x, y, enemigoImg);	
			
			type = "Enemigo";
			
			enemigoImg.flipped = true;			
		}
		
		override public function update():void
		{
			move();
			
			checkAnti_gEffect();
			
			
			super.update();
		}	
		
	
		private function checkAnti_gEffect():void 
		{			
			if (anti_g)
			{
				if (anti_g_carga <= 0)
				{
					desactivaAnti_g();						
				}else
				{
					anti_g_carga -= FP.elapsed;
				}
			}			
		}
		
		private function desactivaAnti_g():void 
		{
			anti_g = false;
			enemigoImg.angle = 0;					
			angulo = 0;			
			enemigoImg.originY += width / 2;
			enemigoImg.originY =  center_y;			
		}
		
		public function get isAntiGEffect():Boolean 
		{
			return anti_g;
		}
		
		public function activaAnti_g():void 
		{					
			anti_g = true;
			anti_g_carga = MAX_anti_g;
			center_y = enemigoImg.originY;
			enemigoImg.originY += width / 2;		
			angulo = 0;			
			vel_x = VEL_X_anti_g * dir_x *SCALE;
			enemigoImg.play("idle")																
		}
		
		
		private function move():void 
		{
			if(dir_x != DIR_NA)
			{
				x += vel_x * FP.elapsed;				
			}
			else if (vel_x != 0)
			{	
				vel_x += FRICCION * dir_x_f * FP.elapsed;					
				x += vel_x * FP.elapsed;
				
				if (vel_x > 0 && dir_x_f > 0 || vel_x < 0 && dir_x_f < 0)
				{
					vel_x = 0;
					dir_x_f = DIR_NA;					
				}
			}
			
			
			if (anti_g)
			{					
				y += GRAVEDAD * 0.10 * FP.elapsed;
				
				if (angulo < 45)
				{					
					if (enemigoImg.flipped)
					{
						enemigoImg.angle = angulo;
					}
					else
					{
						enemigoImg.angle = -angulo;
					}
					angulo++;
				}				
			}
			else
			{			
				if (vel_y > 0 || y < PISO_Y)
				{				
					vel_y += GRAVEDAD * FP.elapsed;	
					y += vel_y * FP.elapsed * -1;
				}
			}
			
			if (y > PISO_Y)
			{
				y = PISO_Y;
				vel_y = 0;
			}
			
		}
		
		public function destroy():void
		{			
			FP.world.remove(this);
		}
	}

}