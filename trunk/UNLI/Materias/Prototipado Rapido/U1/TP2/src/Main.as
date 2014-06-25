package
{
	import net.flashpunk.Engine;
	import net.flashpunk.FP;
	
	/**
	 * ...
	 * @author Acid
	 */
	
	[SWF(width="800",height="600")]
	
	public class Main extends Engine
	{
		
		public function Main():void
		{
			super(800, 600, 30, false);
			
			FP.screen.color = 0x000000;
			FP.console.debug = false;
			//FP.console.enable();
			FP.world = new GameWorld();
			
			//FP.console.enable(); FP.console.toggleKey = 188; // Con esto habilito la consola. Se activa con la tecla ',' (coma).
		}
	
	}

}