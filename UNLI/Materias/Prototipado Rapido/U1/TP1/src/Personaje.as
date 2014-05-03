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
		
	public class Personaje extends Entity 
	{
			
		[Embed(source="swordguy.png")]
		private const PERSONAJE_IMG:Class;
		
		private var personajeImg:Spritemap;
		
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
				
		public function Personaje(x:Number=0, y:Number=0, graphic:Graphic=null, mask:Mask=null) 
		{			
			personajeImg = new Spritemap(PERSONAJE_IMG, 48, 32);
			
			personajeImg.add("idle", [0, 1, 2, 3, 4, 5], 20, true);
			personajeImg.add("slide", [0], 30, true);
			personajeImg.add("run", [6, 7, 8, 9, 10, 11], 30, true);
						
			Input.define("run_r", Key.D, Key.RIGHT);
			Input.define("run_l", Key.A, Key.LEFT);
			Input.define("jump", Key.W, Key.UP);
			Input.define("antiG", Key.SHIFT);
			Input.define("fire", Key.SPACE);
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
			if (Input.pressed("jump") && vel_y == 0 && !anti_g)
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
			
			if (Input.pressed("antiG") )
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
			
			if (Input.pressed("fire"))
			{
				//Dispara y crea antigravedad en los objetos, los mismos levitan
				
				if (FP.world.classCount(ProyectilAntiG) < 10)
				{
					var dirx = 1;
					if (personajeImg.flipped)
					{
						dirx = -1;
					}
					FP.world.add(new ProyectilAntiG(x + width / 2, y + height /2, dirx));
				}
				
			}
			
			move();
			
			checkAnti_gEffect();
			
			super.update();
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