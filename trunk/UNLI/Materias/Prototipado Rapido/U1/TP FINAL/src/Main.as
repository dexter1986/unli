package
{
	import net.flashpunk.Engine;
	import net.flashpunk.FP;
	import net.flashpunk.World;
	/**
	 * ...
	 * @author Acid
	 */
	
	[SWF(width="1024",height="768")]	
	public class Main extends Engine
	{
		private var _Menu:Menu;
		private var _Game:GameWorld;	
		private var _Inicio:Inicio;
		
		private var _level:int = 0;
				
		public function Main():void
		{
			super(1024, 768, 30, false);						
			_Menu = new Menu();
			_Game = new GameWorld();
			_Inicio = new Inicio();
		}
		
		override public function init():void
		{
			trace("The game has started!");			
			FP.world = _Menu;			
			FP.screen.color = 0x000000;	
			
			_Menu.active = false;
			_level = 1;
			
		}
		
		override public function update():void
		{
			super.update();
			if (!FP.world.active)
			{
				switch (_level) 
				{
					case 0:
						FP.world = _Inicio;						
						_level = 1;
					break;
					case 1:
						FP.world = _Game;						
						_level = 2;
					break;			
					case 2:
						FP.world = _Menu;						
						_level = 0;
					break;			
					default:
				}
				_Game.active = true;
				_Menu.active = true;
				_Inicio.active = true;
			}
		}
	}

}