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
		
	public class Personaje extends Entity 
	{
		[Embed(source="GE_ZMG_(9mm).mp3")]
		private	const DISPARO_SND:Class;		
		private	var	disparoSFX:Sfx;
		
		[Embed(source="slap.mp3")]
		private	const HIT_SND:Class;		
		private	var	hitSfx:Sfx;
			
		[Embed(source="swordguy.png")]
		private const PERSONAJE_IMG:Class;
		
		private var personajeImg:Spritemap;
		
		private const SCALE = 1.0;
		private const VEL_X = 200;
		private const VEL_X_anti_g = 50;
		private const VEL_Y = 300;
		private const VEL_Y_JUMP = 300;
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
		private var fireMsk = 0x08;
		private var fireMaxMsk = 0x04;
		private var habilidad = 0x08; 
				
		public function Personaje(x:Number=0, y:Number=0, graphic:Graphic=null, mask:Mask=null) 
		{			
			hitSfx = new Sfx(HIT_SND);
			disparoSFX = new Sfx(DISPARO_SND);
						
			personajeImg = new Spritemap(PERSONAJE_IMG, 48, 32);
			
			personajeImg.add("idle", [0, 1, 2, 3, 4, 5], 20, true);
			personajeImg.add("slide", [0], 30, true);
			personajeImg.add("run", [6, 7, 8, 9, 10, 11], 30, true);
						
			Input.define("run_r", Key.D, Key.RIGHT);
			Input.define("run_l", Key.A, Key.LEFT);
			Input.define("jump", Key.W, Key.UP);
			Input.define("antiG", Key.SHIFT);
			Input.define("fire", Key.SPACE);
			Input.define("fireMax", Key.F);
			Input.define("hit", Key.CONTROL);
			
			setHitbox(48 * SCALE, 32 * SCALE);
			width = 48;
			height = 32;
			
			personajeImg.smooth = true;
			personajeImg.scale = SCALE;
			
			anti_g_carga = MAX_anti_g;
			
			super(x, y, personajeImg);
			
			type = "Personaje";
		}
		
		public function GetAntiG():Number 
		{
			return int(anti_g_carga * 100 / MAX_anti_g);
		}
		
		override public function update():void 
		{
			if (CheckJump() && Input.pressed("jump") && vel_y == 0 && !anti_g)
			{				
				vel_y = VEL_Y_JUMP*SCALE;
				personajeImg.play("slide");
			}
			
			if (Input.check("run_r") && Input.check("run_l") && !anti_g)
			{
				dir_x = DIR_NA;
				personajeImg.play("slide");
			}
			else if (Input.check("run_r")&& vel_y == 0 && !anti_g)
			{
				personajeImg.flipped = false;	
				if (vel_x == 0)
				{					
					dir_x = DIR_R;
					dir_x_f = -dir_x;
					vel_x = VEL_X * dir_x*SCALE;
				}
				if (dir_x != DIR_R)
				{
					personajeImg.play("slide");
					dir_x = DIR_NA;
				}
				else
				{
					personajeImg.play("run");
					vel_x = VEL_X * dir_x*SCALE;
				}				
			}
			else if (Input.check("run_l") && vel_y == 0 && !anti_g)
			{				
				personajeImg.flipped = true;	
				if (vel_x == 0)
				{				
					dir_x = DIR_L;
					dir_x_f = -dir_x;
					vel_x = VEL_X * dir_x*SCALE;
				}
				
				if (dir_x != DIR_L)
				{
					personajeImg.play("slide");
					dir_x = DIR_NA;
				}
				else
				{
					personajeImg.play("run");
					vel_x = VEL_X * dir_x*SCALE;
				}				
			}
			
			if (!Input.check("run_r") && !Input.check("run_l") && vel_y == 0 && !anti_g)
			{					
				if (vel_x != 0)
				{
					personajeImg.play("slide");					
				}
				else 
				{
					personajeImg.play("idle");					
				}
				dir_x = DIR_NA;
			}
			
			if (CheckAntiG() && Input.pressed("antiG"))
			{
				//Activa antigraveda y puede levitar
				if (!anti_g)
				{					
					activaAnti_g();
				}
				else
				{
					desactivaAnti_g();
				}
			}
			
			if (Input.check("hit"))
			{
				//Pega con el arma y daña
			}
			
			if (CheckFire() && Input.pressed("fire"))
			{
				//Dispara y crea antigravedad en los objetos, los mismos levitan
				
				if (FP.world.classCount(Proyectil) < 10)
				{
					var dirx = 1;
					if (personajeImg.flipped)
					{
						dirx = -1;
					}
					disparoSFX.play();
					FP.world.add(new Proyectil(this, x + width / 2, y + height /2, dirx));
				}
				
			}
			
			if (CheckMaxFire() && Input.pressed("fireMax"))
			{	
				if (FP.world.classCount(ProyectilMax) < 10)
				{
					var dirx = 1;
					if (personajeImg.flipped)
					{
						dirx = -1;
					}
					disparoSFX.play();
					FP.world.add(new ProyectilMax(this, x + width / 2, y + height /2 - 10, dirx));
				}
				
			}
			
			move();
			
			checkAnti_gEffect();
			
			super.update();
		}
		
		public function Habilidad():Number
		{
			return habilidad;
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
		
		public function SetOnMaxFire():void
		{
			habilidad |= fireMaxMsk;
		}		
		
		public function SetHabilidad(habilidad:Number):void 
		{
			this.habilidad |= habilidad;
		}
		
		public function CheckJump():Boolean
		{
			return (habilidad & jumpMsk) == jumpMsk;
		}
		
		public function CheckAntiG():Boolean
		{
			return (habilidad & antiGpMsk) == antiGpMsk;
		}
		
		public function CheckMaxFire():Boolean
		{
			return (habilidad & fireMaxMsk) == fireMaxMsk;
		}
		
		public function CheckFire():Boolean
		{
			return (habilidad & fireMsk) == fireMsk;
		}
		
		private function desactivaAnti_g():void 
		{
			anti_g = false;
			personajeImg.angle = 0;					
			angulo = 0;			
			personajeImg.originY += width / 2;
			personajeImg.originY =  center_y;			
		}
		
		private function activaAnti_g():void 
		{		
			if (isAnti_g_cargado)
			{
				anti_g = true;
				center_y = personajeImg.originY;
				personajeImg.originY += width / 2;		
				angulo = 0;			
				vel_x = VEL_X_anti_g * dir_x*SCALE;
				personajeImg.play("slide")													
			}
		}
		
		private function checkAnti_gEffect():void 
		{
			if (anti_g)
			{
				if (anti_g_carga <= 0)
				{
					desactivaAnti_g();	
					isAnti_g_cargado = false;
				}else
				{
					anti_g_carga -= FP.elapsed;
				}
			}
			else
			{	
				if (anti_g_carga < MAX_anti_g)
				{
					anti_g_carga += FP.elapsed;					
					if(anti_g_carga >= MAX_anti_g)
					{
						anti_g_carga = MAX_anti_g;
						isAnti_g_cargado = true;
					}
				}
				if(anti_g_carga > MAX_anti_g)
				{
					anti_g_carga = MAX_anti_g;
					isAnti_g_cargado = true;
				}
			}
		}
		
		public function  Colliding(position:Point):Boolean 
		{
			return collide("Solid", position.x, position.y);
		}
		
		private function move():void 
		{	
			if(dir_x != DIR_NA)
			{
				if (!Colliding(new Point(x + vel_x * FP.elapsed, y)))
				{
					x += vel_x * FP.elapsed;				
				}
				else
				{
					vel_x = 0;
				}
			}
			else if (vel_x != 0)
			{	
				vel_x += FRICCION * dir_x_f * FP.elapsed;	
				
				if (!Colliding(new Point(x + vel_x * FP.elapsed, y)))
				{
					x += vel_x * FP.elapsed;				
				}
				else 
				{
					vel_x = 0;
				}
				
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
					if (personajeImg.flipped)
					{
						personajeImg.angle = angulo;
					}
					else
					{
						personajeImg.angle = -angulo;
					}
					angulo++;
				}				
			}
			else
			{
				if (vel_y > 0 || y < PISO_Y)
				{				
					vel_y += GRAVEDAD * FP.elapsed ;	
					if (!Colliding(new Point(x , y +  vel_y * FP.elapsed  * -1 )))
					{
						y += vel_y * FP.elapsed * -1;
					}
					else
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
		
		public function destroy():void
		{			
			hitSfx.play();
			FP.world.remove(this);
		}
		
	}

}