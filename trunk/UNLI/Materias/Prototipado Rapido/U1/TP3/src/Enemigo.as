package   
{
	import flash.geom.Point;
	import net.flashpunk.Entity;	
	import net.flashpunk.Graphic;
	import net.flashpunk.graphics.Spritemap;
	import net.flashpunk.Mask;
	import net.flashpunk.utils.Input;
	import net.flashpunk.utils.Key;
	import net.flashpunk.FP;
	import net.flashpunk.Sfx;
	
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
		private const VEL_Y_JUMP = 500;
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
		
		private var jumpMsk = 0x01;
		private var antiGpMsk = 0x02;
		private var fireMsk = 0x4;
		private var habilidad = 0x0; 
		
		[Embed(source="GE_ZMG_(9mm).mp3")]
		private	const DISPARO_SND:Class;		
		private	var	disparoSFX:Sfx;
		
		[Embed(source="slap.mp3")]
		private	const HIT_SND:Class;		
		private	var	hitSfx:Sfx;
		
		public function Enemigo(x:Number=0, y:Number=0, graphic:Graphic=null, mask:Mask=null) 
		{
			hitSfx = new Sfx(HIT_SND);
			disparoSFX = new Sfx(DISPARO_SND);
			
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
		
		public function SetOnJump():void
		{
			habilidad |= jumpMsk;
		}
		
		public function SetOnAntiG():void
		{
			habilidad |= antiGpMsk;
		}
		
		public function SetOnFire():void
		{
			habilidad |= fireMsk;
		}
		
		private function move():void 
		{
			if (CheckJump() && vel_y == 0 && !anti_g)
			{				
				vel_y = VEL_Y_JUMP*SCALE;				
			}
			
			if (CheckAntiG())
			{
				//Dispara y crea antigravedad en los objetos, los mismos levitan
				
				if (FP.world.classCount(Proyectil) < 1)
				{
					var dirx = 1;
					if (enemigoImg.flipped)
					{
						dirx = -1;
					}
					disparoSFX.play();
					FP.world.add(new Proyectil(null, x + width / 2  - 25, y + height /2 - 15, dirx));
				}
				
			}
			
			if (CheckFire())
			{								
				if (FP.world.classCount(ProyectilMax) < 1)
				{
					var dirx = 1;
					if (enemigoImg.flipped)
					{
						dirx = -1;
					}
					disparoSFX.play();
					FP.world.add(new ProyectilMax(null, x + width / 2 - 25, y + height /2 - 15, dirx));
				}
				
			}
			
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
					
					if (!Colliding(new Point(x , y +  vel_y * FP.elapsed  * -1 )))
					{
						y += vel_y * FP.elapsed * -1;
					}else
					{
						vel_y = 0;
					}
				}
			}
			
			if (y > PISO_Y)
			{
				y = PISO_Y;
				vel_y = 0;
			}
			
		}
		
		public function  Colliding(position:Point):Boolean 
		{
			return collide("Solid", position.x, position.y);
		}
		
		public function CheckJump():Boolean
		{
			return (habilidad & jumpMsk) == jumpMsk;
		}
		
		public function CheckAntiG():Boolean
		{
			return (habilidad & antiGpMsk) == antiGpMsk;
		}
		
		public function CheckFire():Boolean
		{
			return (habilidad & fireMsk) == fireMsk;
		}
		
		public function Habilidad():Number
		{
			return habilidad;
		}
		
		public function destroy():void
		{			
			hitSfx.play();
			FP.world.remove(this);
		}
	}

}