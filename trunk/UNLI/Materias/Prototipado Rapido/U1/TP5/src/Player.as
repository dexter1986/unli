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
	public class Player extends Entity 
	{
		[Embed(source="BubblePlop.mp3")]
		private	const HIT_SND:Class;		
		private	var	hitSfx:Sfx;
		
		[Embed(source="Mario.png")]
		private const PLAYER_IMG:Class;
		public var playerImage:Spritemap;
		
		[Embed(source="MarioHit.png")]
		private const PLAYER_IMG_HIT:Class;
		private var playerImageHit:Spritemap;
		
		private var grp_List:Graphiclist;
		private var exp_Emiter:Emitter;
		
		public var isDead:Boolean = false;
				
		private const SCALE = 1.5;
		private const VEL_X = 200;
		private const VEL_X_anti_g = 50;
		private const VEL_Y = 500;
		private const VEL_Y_JUMP = 300;
		private const DIR_L = -1;
		private const DIR_R = 1;				
		private const DIR_NA = 0;
		private const GRAVEDAD = -800;
		private const FRICCION = 500;
				
		private const PISO_Y = 490;
		
		private var dir_x_f = 0;
		private var dir_x = 0;		
		private var vel_x = 0;
		private var vel_y = 0;	
		private var center_y = 0;
		private var angulo = 0;		
	
		private var hit:Boolean = false;
		
		public function Player(px:Number = 0, py:Number = 0) 
		{
			hitSfx = new Sfx(HIT_SND);
						
			exp_Emiter = new Emitter(new BitmapData(4,4),4,4);
			exp_Emiter.newType("explode",[0]);			
			exp_Emiter.setMotion("explode", 0, 300, 1, 270, -40, -0.95);
			exp_Emiter.relative = false;
			
			playerImage = new Spritemap(PLAYER_IMG, 37.2, 50);		
			playerImage.add("idle", [0], 30, false);
			playerImage.add("run", [1, 2], 30, true);
			playerImage.add("jump", [3], 30, false);
			
			Input.define("run_r", Key.D, Key.RIGHT);
			Input.define("run_l", Key.A, Key.LEFT);
			Input.define("jump", Key.W, Key.UP);		
			Input.define("hit", Key.SPACE);
			
			playerImageHit = new Spritemap(PLAYER_IMG_HIT,50,50);
			playerImageHit.add("hit", [0,1], 10, false);
			
			grp_List = new Graphiclist(playerImage,exp_Emiter);// , playerImageHit);
			
			setHitbox(50, 50);
			width = 50 ;
			height = 50;
			
			super(px, py, grp_List);		
						
			type = "player";
			playerImage.play("idle");					
		}
		
		override public function update():void
		{	if (!isDead)
			{
			if (!hit)
			{
				if (Input.pressed("jump") && vel_y == 0 )
				{				
					vel_y = VEL_Y_JUMP*SCALE;
					playerImage.play("jump");
				}
				
				if (Input.check("run_r") && Input.check("run_l") )
				{
					dir_x = DIR_NA;
					playerImage.play("idle");
				}
				else if (Input.check("run_r")&& vel_y == 0 )
				{
					playerImage.flipped = true;	
					if (vel_x == 0)
					{					
						dir_x = DIR_R;
						dir_x_f = -dir_x;
						vel_x = VEL_X * dir_x*SCALE;
					}
					if (dir_x != DIR_R)
					{
						playerImage.play("idle");
						dir_x = DIR_NA;
					}
					else
					{
						playerImage.play("run");
						vel_x = VEL_X * dir_x*SCALE;
					}
				}
				else if (Input.check("run_l") && vel_y == 0)
				{
					playerImage.flipped = false;	
					if (vel_x == 0)
					{				
						dir_x = DIR_L;
						dir_x_f = -dir_x;
						vel_x = VEL_X * dir_x*SCALE;
					}
					if (dir_x != DIR_L)
					{
						playerImage.play("idle");
						dir_x = DIR_NA;
					}
					else
					{
						playerImage.play("run");
						vel_x = VEL_X * dir_x*SCALE;
					}
				}
				
				if (!Input.check("run_r") && !Input.check("run_l") && vel_y == 0)
				{	
					if (vel_x != 0)
					{
						playerImage.play("idle");					
					}
					else 
					{
						playerImage.play("idle");					
					}
					dir_x = DIR_NA;
				}
			}
			else
			{
				dir_x = DIR_NA;
			}
			
			if (Input.check("hit"))
			{
				if (!hit)
				{
					hit = true;
					grp_List.remove(playerImage);
					grp_List.add(playerImageHit);
					playerImageHit.play("hit");
					playerImageHit.flipped = playerImage.flipped;		
					setHitbox(100, 100);
					var b:Enemigo = collide("enemigo", x, y) as Enemigo;
					if (b && !b.isDead)
					{	
						b.die();
					}
				}
			}
			else
			{
				if (hit)
				{
					hit = false;
					grp_List.remove(playerImageHit);
					grp_List.add(playerImage);
					playerImage.play("idle");									
				}
				
				setHitbox(25, 25);
				var b:Enemigo = collide("enemigo", x, y) as Enemigo;
				if (b && !b.isDead)
				{	
					b.die();
					this.die();
				}
			}
		   
			
			
			move();
		    }
			if (isDead)
			{
				playerImage.visible = false;
				if(exp_Emiter.particleCount == 0)
				{
					var gWorld:GameWorld = FP.world as GameWorld;
					gWorld.gameReboot();
				}
			}
			super.update();
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
			
				
			if (vel_y > 0 || y < PISO_Y)
			{				
				vel_y += GRAVEDAD * FP.elapsed;	
				y += vel_y * FP.elapsed * -1;
			}
			
			if (y > PISO_Y)
			{
				y = PISO_Y;
				vel_y = 0;
			}
		}
		
		public function getWidth():Number
		{
			return (playerImage.width / playerImage.columns);
		}
		
		public function getHeight():Number
		{
			return (playerImage.height / playerImage.rows);
		}
		
		public function  die():void 
		{	
			if (!isDead)
			{
				hitSfx.play();
				isDead = true;
				this.collidable = false;								
				exp_Emiter.setColor("explode", 0xFF0000, 0xFFFFFF);
				for (var i:uint = 0; i < 500; i++)
				{
					exp_Emiter.emit("explode", x + width / 2, y + height / 2);
				}
			}
		}
	}
}
