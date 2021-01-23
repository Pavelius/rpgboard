#include "main.h"

static varianta all_abilities = {Strenght, Dexterity, Constitution, Intellegence, Wisdow, Charisma};
static varianta all_languages = {LanguageCommon, LanguageDwarvish, LanguageHalfling, LanguageElvish, LanguageGiant, LanguageGoblin, LanguageOrc, LanguageAbysal, LanguageCelestial, LanguageDraconic, LanguageDeepSpeech, LanguageInfernal};
static varianta cleric_cantrips = {Guidance, Light, Resistance, SacredFlame, SpareTheDying, Thaumaturgy};
static varianta artisan_tools = {CarpentersTools, CartographersTools, CobblersTools, GlassblowersTools, JewelersTools, LeatherworkersTools, MassonsTools, PottersTools, SmithsTools, TinkersTools, WeaversTools, WoodcuttersTools};
static varianta game_set = {Dices, DragonChess, PlayingCards, ThreeDragonAnte};

BSDATA(levelupi) = {
	{"Ability Score Increase", Dwarf, 0, {Constitution, Constitution}},
	{"Speed", Dwarf, 0, {Minus, Speed, DoNotSlowByArmor}},
	{"Darkvision", Dwarf, 0, {Darkvision}},
	{"Dwarven Resilience", Dwarf, 0, {Advantage, SaveVsPoison, Resist, Poison}},
	{"Dwarven Combat Training", Dwarf, 0, {Battleaxe, Handaxe, Warhammer, Lighthammer}},
	{"Tools Proficiencies", Dwarf, 0, {}},
	{"Stonecunning", Dwarf, 0, {Stonecunning}},
	{"Languages", Dwarf, 0, {LanguageCommon, LanguageDwarvish}},
	{"Ability Score Increase", DwarfHill, 0, {Wisdow}},
	{"Dwarven toughness", DwarfHill, 0, {HitPoints}},
	{"Ability Score Increase", DwarfMountain, 0, {Strenght, Strenght}},
	{"Dwarven Armor Training", DwarfMountain, 0, {LeatherArmor, StuddedLeather, PaddedArmor, HideArmor, ChainShirt, ScaleMail, Breastplate, HalfPlate}},
	{"Ability Score Increase", Elf, 0, {Dexterity, Dexterity}},
	{"Darkvision", Elf, 0, {Darkvision}},
	{"Keen senses", Elf, 0, {Perception}},
	{"Fey Ancestry", Elf, 0, {Advantage, SaveVsCharm, ImmunitySleep}},
	{"Trance", Elf, 0},
	{"Languages", Elf, 0, {LanguageCommon, LanguageElvish}},
	{"Ability Score Increase", ElfHight, 0, {Intellegence}},
	{"Elf Weapon Training", ElfHight, 0, {Longbow, Longsword, Shortbow, Shortsword}},
	{"Cantrip", ElfHight, 0, {Longbow, Longsword, Shortbow, Shortsword}},
	{"Extra Languages", ElfHight, 0, all_languages, 1},
	{"Ability Score Increase", ElfWood, 0, {Wisdow}},
	{"Elf Weapon Training", ElfWood, 0, {Longbow, Longsword, Shortbow, Shortsword}},
	{"Fleet of Foot", ElfWood, 0, {Speed}},
	{"Mask of the Wild", ElfWood, 0, {HideWhenLightObscured}},
	{"Ability Score Increase", Halfling, 0, {Dexterity, Dexterity}},
	{"Speed", Halfling, 0, {Minus, Speed}},
	{"Brave", Halfling, 0, {Advantage, SaveVsFear}},
	{"Halfling Nimbleness", Halfling, 0, {Nimbless}},
	{"Languages", Halfling, 0, {LanguageCommon, LanguageHalfling}},
	{"Ability Score Increase", HalflingLightfoot, 0, {Charisma}},
	{"Naturaly stealthy", HalflingLightfoot, 0, {HideWhenObscuredLargerCreature}},
	{"Ability Score Increase", HalflingLightfoot, 0, {Constitution}},
	{"Stout Resilence", HalflingStout, 0, {Advantage, SaveVsPoison, Resist, Poison}},
	{"Ability Score Increase", Human, 0, {Strenght, Dexterity, Constitution, Intellegence, Wisdow, Charisma}},
	{"Skill Proficiencies", Acolyte, 0, {Insight, Religion}},
	{"Languages", Acolyte, 0, all_languages, 2},
	{"Skill Proficiencies", Criminal, 0, {Deception, Stealth}},
	{"Tools Proficiencies", Criminal, 0, {TheivesTools}},
	{"Tools Proficiencies", Criminal, 0, game_set, 1},
	{"Skill Proficiencies", FolkHero, 0, {Survival, AnimalHandling}},
	{"Tools Proficiencies", FolkHero, 0, {Horse}},
	{"Tools Proficiencies", FolkHero, 0, artisan_tools, 1},
	{"Skill Proficiencies", Noble, 0, {History, Persuasion}},
	{"Tools Proficiencies", Noble, 0, game_set, 1},
	{"Languages", Noble, 0, all_languages, 1},
	{"Skill Proficiencies", Sage, 0, {Arcana, History}},
	{"Languages", Sage, 0, all_languages, 2},
	{"Skill Proficiencies", Soldier, 0, {Athletics, Intimidation}},
	{"Tools Proficiencies", Soldier, 0, game_set, 1},
	{"Tools Proficiencies", Soldier, 0, {Horse}},
	{"Armor", Cleric, 1, {LightArmor, MediumArmor, Shields}},
	{"Weapons", Cleric, 1, {SimpleWeapons}},
	{"Saving Throws", Cleric, 1, {SaveVsWisdow, SaveVsCharisma}},
	{"Skill Proficiencies", Cleric, 1, {History, Insight, Medicine, Persuasion, Religion}, 2},
	{"Cantrips", Cleric, 1, cleric_cantrips, 3},
	{"Spellcasting Focus", Cleric, 1, {Focus, HolySymbol}},
	{"Channel Divinity", Cleric, 1, {TurnUndead, ChannelDivinitySlot}},
	{"Ability Score Improvement", Cleric, 4, all_abilities, 2},
	{"Ability Score Improvement", Cleric, 8, all_abilities, 2},
	{"Ability Score Improvement", Cleric, 12, all_abilities, 2},
	{"Ability Score Improvement", Cleric, 16, all_abilities, 2},
	{"Ability Score Improvement", Cleric, 19, all_abilities, 2},
	{"Armor", Fighter, 1, {LightArmor, MediumArmor, HeavyArmor, Shields}},
	{"Weapons", Fighter, 1, {SimpleWeapons, MartialWeapons}},
	{"Saving Throws", Fighter, 1, {SaveVsStrenght, SaveVsConstitution}},
	{"Skill Proficiencies", Fighter, 1, {Acrobatics, AnimalHandling, Athletics, History, Insight, Intimidation,	Perception, Survival}, 2},
	{"Fighting style", Fighter, 1, {Archery, Defense, Dueling, GreatWeaponFighting, Protection, TwoWeaponFighting}, 1},
	{"Second wind", Fighter, 1, {SecondWind, SecondWindSlot}},
	{"Action Surge", Fighter, 2, {ActionSurge, ActionSurgeSlot}},
	{"Extra attack", Fighter, 5, {ExtraAttack}},
	{"Extra attack", Fighter, 11, {ThirdAttacks}},
	{"Extra attack", Fighter, 11, {FourthAttacks}},
};
BSDATAF(levelupi)

void creaturei::apply(const varianta& source, modifier_s m) {
	for(auto v : source) {
		switch(v.type) {
		case Modifier: m = modifier_s(v.value); break;
		case Pack: apply(bsdata<packi>::elements[v.value].source, m); break;
		default: apply(v, m); break;
		}
	}
}

bool creaturei::have(variant v) const {
	switch(v.type) {
	case Item: return proficiency.is(v.value);
	case FightingStyle: return fightstyle.is(v.value);
	case Language: return languages.is(v.value);
	case Skill: return skills.is(v.value);
	case Spell: return spells_known.is(v.value);
	case Trait: return traits.is(v.value);
	default: return false;
	}
}

void creaturei::apply(variant v, modifier_s m) {
	switch(v.type) {
	case Ability:
		switch(m) {
		case Minus: abilities[v.value] -= 1; break;
		default: abilities[v.value] += 1; break;
		}
		break;
	case Item:
		switch(m) {
		case Focus: spells_focus.set(v.value); break;
		default: proficiency.set(v.value); break;
		}
		break;
	case Language:
		languages.set(v.value);
		break;
	case Skill:
		switch(m) {
		case Advantage:	skills_advantage.set(v.value); break;
		case DoubleMastery: skills_double.set(v.value); break;
		default: skills.set(v.value); break;
		}
		break;
	case Spell:
		spells_known.set(v.value);
		break;
	case Trait:
		traits.set(v.value);
		break;
	case FightingStyle:
		fightstyle.set(v.value);
		break;
	default:
		break;
	}
}

void creaturei::apply(variant object, int level, bool interactive) {
	for(auto& ei : bsdata<levelupi>()) {
		if(ei.level != level)
			continue;
		if(ei.object != object)
			continue;
		if(ei.count) {
			for(auto i = ei.count; i > 0; i--) {
				variantc source;
				for(auto e : ei.source) {
					if(have(e))
						continue;
					source.add(e);
				}
				source.sort();
				variant v1 = source.chooseg(ei.name, ei.text, i);
				apply(v1, NoModifier);
			}
		} else
			apply(ei.source);
	}
}