import flixel.FlxSprite;

class Bullet extends FlxSprite{
    public function new(){
        super();
        makeGraphic(4, 4, 0xffffffff, false, "bullet_graph");
    }

    public override function update(): Void {
    	super.update();    	
        if (!isOnScreen())
		{
            kill();
		}
    }
}