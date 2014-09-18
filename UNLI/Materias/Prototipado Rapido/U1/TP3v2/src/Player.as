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
	import net.flashpunk.tweens.misc.MultiVarTween;
		
	/**
	 * ...
	 * @author ...
	 */
	public class Player extends Entity 
	{	
		[Embed(source="textura.png")]
		private const PLAYER_IMG:Class;
		public var playerImage:Spritemap;	
		private var scale:Number = 0.5;
		private var playerTween:MultiVarTween;
		protected var playerStatus:String = "END";		
		private var exp_Emiter:Emitter;
		private var grp_List:Graphiclist;
		public var isDead:Boolean = false;
		
		private var tempposx:Number;
		private var tempposy:Number;
		
		private var posx:Number;
		private var posy:Number;
		
		private var InitColor:uint;
		
		public function Player(px:Number = 0, py:Number = 0) 
		{			
			playerImage = new Spritemap(PLAYER_IMG,128,128);
			playerImage.add("idle", [3], 1, false);
			playerImage.scale = scale;
			
			setHitbox(128*scale, 128*scale);
			width = 128;
			height = 128;
			
			exp_Emiter = new Emitter(new BitmapData(2, 2), 2,2);
			exp_Emiter.newType("explode", [0]);
			exp_Emiter.setAlpha("explode", 1, 0);
			exp_Emiter.setMotion("explode", 0, 150, 1, 360, -40,-0.5,Ease.quadOut);
			exp_Emiter.relative = false;
			
			grp_List = new Graphiclist(playerImage,exp_Emiter);	
			
			super(px, py, grp_List);				
						
			type = "player";	
			playerImage.play("idle");
			
			playerTween = new MultiVarTween();
			
			FP.world.addTween(playerTween);	
			visible = false;
		}
		
		private var tempColor:uint;
		private var tempIsKey:Boolean;
		
		override public function update():void
		{	
			if (isDead)
			{	
				this.playerImage.visible = false;
				if (exp_Emiter.particleCount == 0)
				{
					var world:GameWorld = FP.world as GameWorld;						
					if (!world.RestartGame)
					{
						world.RestartGame = true;
					}
				}								
			}
			else
			{			
				if (playerStatus == "END")
				{
					if (Input.mousePressed)
					{
						var b:Simbolo = collide("Simbolo", Input.mouseX, Input.mouseY) as Simbolo;				
						if (b)
						{	
							tempIsKey = b.IsKey();
							tempColor = b.GetColor();
							playerStatus = "START";
							posx = b.x;
							posy = b.y;
							playerTween.tween(this, { x:posx, y:posy }, 1, Ease.backInOut);			
							playerTween.start();						
						}
					}
				}
				else
				{
					if (this.x == posx && this.y == posy)
					{
						playerStatus = "END";
						if (tempIsKey)
						{
							if (tempColor == GetColor())
							{
								(FP.world as GameWorld).NextLevel();								
								//(FP.world as GameWorld).RestartGame = true;
							}
							else
							{
								die();
							}
						}else
						{
							SetColor(tempColor);
						}
					}
					playerTween.update();
				}
			}
			super.update();
		}
		
		private function SetColor(color:uint)
		{			
			if (playerImage.color == InitColor)
			{
				playerImage.color = color;
			}
			else
			{
				playerImage.color |= color;
			}
		}
		
		private function GetColor():uint
		{
			return playerImage.color;
		}
		
		public function Setup(px:Number, py:Number):void 
		{
			tempposx = px;
			tempposy = py;
		}
		
		
		public function Init(color:uint):void 
		{
			isDead = false;
			SetColor(color);
			this.x = tempposx;
			this.y = tempposy;
			this.playerStatus = "END";	
			this.isDead = false;
			this.visible = true;
			this.collidable = true;
			this.playerImage.visible = true;	
			this.InitColor = color;
		}
		
		public function  die():void 
		{
			if (!isDead)
			{
				isDead = true;
				this.collidable = false;								
				exp_Emiter.setColor("explode", 0xFF0000, 0xFFFFFF);
				for (var i:uint = 0; i < 100; i++)
				{
					exp_Emiter.emit("explode", x + (width /2)*scale, y + (height /2)*scale);
				}
			}
		}
		
		private function move():void 
		{
			
		}
	}
}
