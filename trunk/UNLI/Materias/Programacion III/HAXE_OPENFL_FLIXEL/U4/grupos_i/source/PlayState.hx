import flixel.FlxBasic;
import flixel.FlxG;
import flixel.FlxSprite;
import flixel.FlxState;
import flixel.group.FlxGroup;
import flixel.text.FlxText;
import flixel.util.FlxRandom;

class PlayState extends FlxState
{
	private var hero: Hero;
	private var enemies: FlxGroup;
	private var board: MessageBoard;
	private var sword: Sword;
	private var energyText: FlxText;
	
	override public function create():Void
	{
		super.create();
		add(new FlxSprite(0, 0, "assets/images/background.png"));
		// creamos un grupo para contener a los enemigos
		enemies = new FlxGroup();
		// agregamos enemigos al grupo
		for(i in 0...5)
		{
			var x = FlxRandom.intRanged(0, 19) * 16;
			var y = FlxRandom.intRanged(0, 14) * 16;
			enemies.add(new Monster(x, y));
		}
		// agregamos al grupo a la escena
		add(enemies);
		
		sword = new Sword(160, 160);
		add(sword);

		hero = new Hero(128, 128);
		add(hero);
		
		add(hero.bullets);

		board = new MessageBoard();
		add(board);

		energyText = new FlxText(0, 0, 200);
		updateEnergyText();
		add(energyText);
	}
	
	override public function update():Void
	{
		super.update();
		// comprobamos si colisiona el heroe con los enemigos
		FlxG.overlap(hero, enemies, onOverlapHeroEntities);
		FlxG.overlap(hero, sword, onOverlapHeroEntities);
	
		FlxG.overlap(hero.bullets,enemies, onEnemyHit);
		
		// controlamos la condición de victoria
		if(enemies.countLiving() <= 0)
		{
			board.showMessage("You WON!!!!");
		}
	}

	private function onOverlapHeroEntities(TheHero: FlxBasic, TheEntity: FlxBasic){
		// guardamos en una variable la clase del objeto TheEntity
		var entityClass = Type.getClass(TheEntity);
		// si es un monstruo...
		if(entityClass == Monster)
		{
			// convertimos la referencia tipo FlxBasic a otra de tipo Hero
			var theHero: Hero = cast(TheHero, Hero);
			theHero.receiveDamage();
			updateEnergyText();
			if(theHero.energy == 0)
			{
				theHero.kill();
				board.showMessage("You've been killed... :(");
			}
		}
		// si colisionamos con la espada...
		else if(entityClass == Sword)
		{
			TheEntity.kill();
			board.showMessage("You've found a sword!");
		}	
	}
	
	// es llamada cuando un enemigo es golpeado por un proyectil de la nave 
	private function onEnemyHit(TheBullet: FlxBasic, TheEnemy: FlxBasic)
	{
		TheBullet.kill();
		TheEnemy.kill();
	}

	private function updateEnergyText()
	{
		energyText.text = "Energy  ";
		for(i in 0...hero.energy)
		{
			energyText.text += "| ";
		}
	}
}