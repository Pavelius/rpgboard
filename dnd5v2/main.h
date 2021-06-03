#include "crt.h"
#include "point.h"
#include "stringbuilder.h"

#pragma once

enum modifier_s : unsigned char {
	NoModifier, Advantage, DoubleMastery, Focus, Resist, Immune, Minus, Vulnerable,
};
enum damage_s : unsigned char {
	Acid, Bludgeoning, Cold, Fire, Force,
	Lightning, Necrotic, Piercing, Poison, Psychic,
	Radiant, Slashing, Thunder,
	Healing,
};
enum skill_s : unsigned char {
	Athletics, Acrobatics, SleightOfHands, Stealth,
	Arcana, History, Investigation, Nature, Religion,
	AnimalHandling, Insight, Medicine, Perception, Survival,
	Deception, Intimidation, Performance, Persuasion,
};
enum background_s : unsigned char {
	Acolyte, Criminal, FolkHero, Noble, Sage, Soldier,
};
enum generate_s : unsigned char {
	ChooseAbilities, ChooseAlignment, ChooseBackground, ChooseClass, ChooseGender, ChoosePortrait, ChooseRace,
};
enum pack_s : unsigned char {
	LightArmor, MediumArmor, HeavyArmor, Shields,
	SimpleWeapons, MartialWeapons, CommonLanguages
};
enum tag_s : unsigned char {
	Verbal, Somatic, Material, Ritual,
	NeedAttack, ExtraCreature, ExtraDice,
};
enum fighting_style_s : unsigned char {
	Archery, Defense, Dueling, GreatWeaponFighting, Protection, TwoWeaponFighting,
};
enum item_s : unsigned char {
	NoItem,
	Club, Dagger, Greatclub, Handaxe, Javelin, Lighthammer, Mace, Quarterstaff, Sickle, Spear,
	Crossbow, Dart, Shortbow, Sling,
	Battleaxe, Flail, Glaive, Greataxe, Greatsword, Halberd, Lance,
	Longsword, Maul, Morningstar, Pike, Rapier, Scimitar, Shortsword,
	Trident, Warpick, Warhammer, Whip,
	Blowgun, CrossbowHand, CrossbowHeavy, Longbow, Net,
	PaddedArmor, LeatherArmor, StuddedLeather,
	HideArmor, ChainShirt, ScaleMail, Breastplate, HalfPlate,
	RingMail, ChainMail, SplintArmor, PlateArmor,
	Shield, Hemlet, Hat, Bracers, Gridle,
	ArcaneScroll, DivineScroll, Wand, Book, HolySymbol,
	CarpentersTools, CartographersTools,
	CobblersTools, GlassblowersTools,
	JewelersTools, LeatherworkersTools, MassonsTools,
	PottersTools, SmithsTools, TinkersTools, WeaversTools, WoodcuttersTools,
	DisguiseKit, ForgeryKit,
	Dices, DragonChess, PlayingCards, ThreeDragonAnte,
	HerbalismKit,
	Bagpipes, Flute, Horn, Lute, Lyre, PanFlute, Viol,
	NavigatorsTools, PoisonersKit, TheivesTools,
	Horse, Cab, Ship,
};
enum domain_s : unsigned char {
	KnowledgeDomain, LifeDomain, LightDomain, NatureDomain,
	TempestDomain, TrickeryDomain, WarDomain,
};
enum language_type_s : unsigned char {
	AnyLanguage,
	ModernLanguage, AncientLanguage,
};
enum language_s : unsigned char {
	LanguageCommon,
	LanguageDwarvish, LanguageHalfling, LanguageElvish,
	LanguageGiant, LanguageGoblin, LanguageOrc,
	LanguageAbysal, LanguageCelestial, LanguageDraconic, LanguageDeepSpeech,
	LanguageInfernal,
};
enum school_s : unsigned char {
	Abjuration, Conjuration, Divination, Enchantment, Evocation, Illusion, Necromancy, Transmutation,
};
enum race_s : unsigned char {
	Dwarf, Elf, Halfling, Human,
	DwarfHill, DwarfMountain, ElfWood, ElfHight, HalflingLightfoot, HalflingStout,
};
enum class_s : unsigned char {
	Cleric, Fighter, Rogue, Wizard,
};
enum alignment_s : unsigned char {
	LawfulGood, NeutralGood, ChaoticGood,
	LawfulNeutral, TrueNeutral, ChaoticNeutral,
	LawfulEvil, NeutralEvil, ChaoticEvil,
};
enum ability_s : unsigned char {
	Strenght, Dexterity, Constitution, Intellegence, Wisdow, Charisma,
	HitPoints, Speed, Movement,
	Attack, MeleeAttack, MissileAttack, Damage, MeleeDamage, MissileDamage,
	ArmorClass, ArmorReduction,
	ActionSurgeSlot, ChannelDivinitySlot, SecondWindSlot,
	StandartActionSlot, BonusActionSlot,
	Spell1, Spell2, Spell3, Spell4, Spell5, Spell6, Spell7, Spell8, Spell9,
};
enum gender_s : unsigned char {
	Male, Female
};
enum size_s : unsigned char {
	Tiny, Small, Medium, Large, Huge,
};
enum range_s : unsigned char {
	Self,
	Touch, Range10, Range20, Range30, Range60, Range80, Range120,
};
enum duration_s : unsigned char {
	Instantaneous, Concentration, BonusAction, StandartAction,
	DurationRound, DurationMinute, Duration10Minute, DurationHour, DurationNight,
};
enum spell_s : unsigned char {
	Guidance, Light, Resistance, SacredFlame, SpareTheDying, Thaumaturgy,
	AcidSplash, DancingLights, FireBolt, MageHand, MinorIllusion, PoisonSpray, Prestidigitation, RayOfFrost, ShockingGrasp,
	Bless, Command, CureWounds, DetectMagic, GuidingBolt, HealingWord, InflictWounds, Sanctuary, ShieldOfFaith,
};
enum resource_s : unsigned char {
	ResNone,
	ResDungeon, ResAvatars, ResMonsters, ResNPC,
};
enum uses_s : unsigned char {
	ManyTimes, Recharge56, Recharge6, UntilShortRest, UntilLongRest
};
enum direction_s : unsigned char {
	Center,
	Up, UpRight, Right, DownRight, Down, DownLeft, Left, UpLeft,
};
enum state_s : unsigned char {
	Active, Hostile,
};
enum save_s : unsigned char {
	SaveVsStrenght, SaveVsDexterity, SaveVsConstitution, SaveVsIntellegence, SaveVsWisdow, SaveVsCharisma,
	SaveVsCharm, SaveVsFear, SaveVsPoison,
};
enum trait_s : unsigned char {
	Darkvision,
	ActionSurge, Stonecunning, ImmunitySleep, DestroyUndead, DoNotSlowByArmor, ExtraAttack,
	FourthAttacks, HideWhenLightObscured, HideWhenObscuredLargerCreature, Nimbless, Lucky,
	RitualCasting, SecondWind, ThirdAttacks, TurnUndead
};
enum variant_s : unsigned char {
	NoVariant,
	Ability, Action, Alignment, Background, Class, Creature, DamageType, Domain, FightingStyle,
	Gender, Generate, Item, Language, Levelup, Menu, Modifier, Pack, Race, Save, School, Skill, Spell, Trait,
};
enum action_s : unsigned char {
	ActionEndTurn,
	ActionAmbush, ActionAttack, ActionDash, ActionDisengage,
	ActionDodge, ActionFeint, ActionHide, ActionReady, ActionSearch, ActionUseItem,
};
const int grid_size = 64;
class creaturei;
typedef cflags<action_s> actionf;
typedef cflags<state_s> statef;
typedef flagable<Material> tagf;
typedef flagable<TwoWeaponFighting> fightstylef;
typedef flagable<TurnUndead> traitf;
typedef flagable<Survival> skillf;
typedef flagable<ShockingGrasp> spellf;
typedef flagable<Ship> itemf;
typedef flagable<LanguageInfernal> languagef;
typedef cflags<damage_s, unsigned short> damagef;
struct variant {
	variant_s			type;
	unsigned char		value;
	constexpr variant() : type(NoVariant), value(0) {}
	constexpr variant(variant_s t, unsigned char v) : type(t), value(v) {}
	constexpr variant(ability_s v) : variant(Ability, v) {}
	constexpr variant(action_s v) : variant(Action, v) {}
	constexpr variant(alignment_s v) : variant(Alignment, v) {}
	constexpr variant(background_s v) : variant(Background, v) {}
	constexpr variant(class_s v) : variant(Class, v) {}
	constexpr variant(damage_s v) : variant(DamageType, v) {}
	constexpr variant(fighting_style_s v) : variant(FightingStyle, v) {}
	constexpr variant(item_s v) : variant(Item, v) {}
	constexpr variant(language_s v) : variant(Language, v) {}
	constexpr variant(modifier_s v) : variant(Modifier, v) {}
	constexpr variant(pack_s v) : variant(Pack, v) {}
	constexpr variant(race_s v) : variant(Race, v) {}
	constexpr variant(save_s v) : variant(Save, v) {}
	constexpr variant(school_s v) : variant(School, v) {}
	constexpr variant(skill_s v) : variant(Skill, v) {}
	constexpr variant(spell_s v) : variant(Spell, v) {}
	constexpr variant(trait_s v) : variant(Trait, v) {}
	variant(const void* v);
	constexpr explicit operator bool() const { return type != NoVariant; }
	constexpr bool operator==(const variant& v) const { return v.type == type && v.value == value; }
	constexpr bool operator!=(const variant& v) const { return (v.type != type) || (v.value != value); }
	const char*			getinfo(stringbuilder& sb) const;
	const char*			getname() const;
	void*				getobject() const;
	void*				getobject(variant_s t) const;
	creaturei*			getcreature() const { return (creaturei*)getobject(Creature); }
};
typedef std::initializer_list<variant> varianta;
struct variantc : adat<variant> {
	variantc() = default;
	variantc(const array& v) { select(v); }
	void				exclude(variant v);
	variant				choose(const char* title, int score = 0) const;
	void				match(action_s v, bool keep);
	void				match(state_s v, bool keep);
	void				match(variant v1, bool keep);
	void				matchbs(bool keep);
	void				range(point start, unsigned v, bool keep);
	void				select(const array& source);
	void				sort();
};
struct varianti {
	const char*			id;
	array*				source;
	unsigned			locale[2];
	unsigned			special[2];
	fntext				getinfo;
	const char*			name;
	const char*			text;
	static void			localization(const char* locale, bool writemode);
};
struct fighting_stylei {
	const char*			id;
	const char*			name;
	const char*			text;
};
struct harmi {
	damage_s			type;
	char				c, d, b;
};
struct abilityi {
	const char*			id;
	const char*			name;
	const char*			text;
};
struct levelupi {
	const char*			id;
	variant				object;
	int					level;
	const varianta		source;
	int					count;
	const char*			name;
	const char*			text;
};
struct packi {
	const char*			id;
	varianta			source;
	const char*			name;
	const char*			text;
};
struct generatei {
	const char*			id;
	int					index, subindex;
	const char*			name;
	const char*			text;
};
struct racei {
	const char*			id;
	race_s				base;
	const char*			name;
	const char*			text;
};
struct traiti {
	const char*			id;
	array*				source;
	const char*			name;
	const char*			text;
};
struct itemi {
	const char*			id;
	const char*			name;
	const char*			text;
};
struct languagei {
	const char*			id;
	const char*			name;
	const char*			text;
};
struct alignmenti {
	const char*			id;
	const char*			name;
	const char*			text;
};
struct backgroundi {
	const char*			id;
	const char*			name;
	const char*			text;
};
struct domaini {
	const char*			id;
	spell_s				spells[2 * 5];
	const char*			name;
	const char*			text;
};
struct genderi {
	const char*			id;
	const char*			name;
	const char*			text;
};
struct skilli {
	const char*			id;
	const char*			name;
	const char*			text;
};
struct schooli {
	const char*			id;
	const char*			name;
	const char*			text;
};
struct savei {
	const char*			id;
	ability_s			ability;
	const char*			name;
	const char*			text;
};
struct spelli {
	const char*			id;
	char				level;
	school_s			school;
	duration_s			action;
	range_s				range;
	tagf				flags;
	duration_s			duration;
	harmi				damage;
	const char*			name;
	const char*			text;
};
struct activityi {
	variant				target;
	variant				creator;
	spell_s				effect;
	unsigned			round;
	int					param;
	constexpr explicit operator bool() const { return target.type != NoVariant; }
};
class nameablei : public variant {
	gender_s			gender;
public:
	gender_s			getgender() const { return gender; }
	const char*			getname() const { return "Object"; }
	race_s				getrace() const;
	void				setkind(variant v);
};
struct classi {
	const char*			id;
	ability_s			abilities[3];
	unsigned char		hd;
	save_s				saves[2];
	skillf				skills;
	const char*			name;
	const char*			text;
};
struct resourcei {
	const char*			name;
	const char*			folder;
	void*				data;
	bool				error;
	void				geturl(stringbuilder& sb) const;
};
struct tilei {
	typedef unsigned char indext;
	const char*			id;
	unsigned char		size;
	unsigned char		block[8 * 8];
	void				edit();
	void				exportdata() const;
	static indext		gi(int x, int y) { return y * 8 + x; }
	static int			gx(indext i) { return i / 8; }
	static int			gy(indext i) { return i % 8; }
	bool				isblocked(indext i) const;
};
class drawable : public point {
	resource_s			rid;
	unsigned short		frame;
	unsigned short		flags;
public:
	static bool			change_position;
	void				clear() { memset(this, 0, sizeof(*this)); }
	static bool			ischangedposition(const void* object);
	bool				isblocked(int x, int y) const;
	void				paint(int x, int y, bool allow_select) const;
	void				setframe(resource_s r, int frame);
	void				setmirrorh(bool v);
	void				setmirrorv(bool v);
	void				setposition(point v);
};
struct damagei {
	const char*			id;
	const char*			name;
	const char*			text;
};
struct statistic {
	unsigned char		abilities[Spell9 + 1];
	traitf				traits;
	skillf				skills, skills_advantage, skills_double;
	damagef				damage_resist, damage_immunity, damage_vulnerable;
	itemf				items_proficiency, items_mastery;
	languagef			languages;
	fightstylef			fightstyle;
	static ability_s	all_abilities[6];
	bool				choose_ability(generate_s id);
	bool				choose_ability(const char* step, const char* title, int score_maximum);
	static int			choose_frame(resource_s resource, const char* header, const char* description, point size);
	int					getabilityscore(int v);
	int					getabilityscores(char* modificators) const;
	void				random_ability(class_s clas);
};
struct rollstati {
	int					r1, r2;
	int					dc;
};
class creaturei : public statistic, public drawable, public nameablei {
	unsigned char		classes[Rogue + 1];
	statistic			base;
	statef				state;
	actionf				actions;
	spellf				spells_known;
	itemf				spells_focus;
	alignment_s			alignment;
	domain_s			domain;
	void				apply(variant v, modifier_s modifier);
	void				apply(variant object, int level, bool interactive);
	void				finish();
	bool				have(variant v, modifier_s modifier) const;
public:
	void				add(ability_s v, int i) { set(v, get(v) + i); }
	void				aftercombatround();
	void				apply(const varianta& source, modifier_s modifier = NoModifier);
	bool				attack(creaturei* target, int bonus, int advantages);
	void				beforecombatround();
	void				clear() { memset(this, 0, sizeof(*this)); }
	void				create(race_s race, class_s clas, gender_s gender);
	bool				feint(creaturei* target, bool run);
	int					get(ability_s v) const { return abilities[v]; }
	bool				generate(bool interactive);
	alignment_s			getalignment() const { return alignment; }
	bool				is(action_s v) const { return actions.is(v); }
	bool				is(trait_s v) const { return traits.is(v); }
	bool				is(state_s v) const { return state.is(v); }
	bool				isfocus(item_s v) { return spells_focus.is(v); }
	bool				isproficiency(item_s v) const { return items_proficiency.is(v); }
	bool				isreadytohide() const;
	void				paint(int x0, int y0, bool allow_drag, bool allow_click) const;
	void				remove(trait_s v) { traits.remove(v); }
	int					roll(int advantages) const;
	static int			roll20(bool halfling_luck);
	void				set(ability_s v, int i) { abilities[v] = i; }
	void				set(action_s v) { actions.add(v); }
	void				set(class_s v, int i) { classes[v] = i; }
	void				set(state_s v) { state.add(v); }
	void				set(trait_s v) { traits.set(v); }
	void				uicombat();
	bool				use(action_s id, bool run);
};
struct actioni {
	const char*			id;
	duration_s			duration;
	const char*			text;
	const char*			name;
};
class answers {
	char				buffer[2048];
	stringbuilder		sc;
	struct element {
		int				id;
		const char*		text;
	};
public:
	answers();
	adat<element, 32>	elements;
	void				add(int id, const char* name, ...) { addv(id, name, xva_start(name)); }
	void				addv(int id, const char* name, const char* format);
	const element*		choosev(const char* title, const char* cancel_text, bool interactive, resource_s id, short unsigned frame, fnvisible allow, const void* object, fntext tips) const;
	int					choose(const char* title, bool allow_cancel, bool interactive, fntext tips = 0) const;
	static int			compare(const void* v1, const void* v2);
	int					random() const;
	void				sort();
};
struct menu {
	const char*			id;
	const char*			parent;
	fnevent				command;
	fnvisible			visible;
	const char*			name;
	const char*			text;
	static const menu*	choose(const char* name, bool allow_back = false);
	static void			run(const char* name);
	static void			select(answers& aw, const char* name);
};
struct gamei {
	void				combat();
};
namespace draw {
typedef void(*callback)();
point					choosepoint();
void					initialize();
}
namespace network {
bool					connect();
void					disconnect();
void					exchange();
}
template<class T> const char* getinfo(const void* object, stringbuilder& sb) { return ((T*)object)->text; }
template<> const char* getinfo<racei>(const void* object, stringbuilder& sb);
int						distance(point p1, point p2);
bool					dlgask(const char* format, ...);
extern gamei			game;
inline int				m2s(int v) { return v * grid_size; }
inline point			m2s(point v) { return {v.x * (short)grid_size, v.y * (short)grid_size}; }
inline short			s2m(int v) { return (v >= 0) ? v / grid_size : (v - grid_size) / grid_size; }
inline point			s2m(point v) { return {s2m(v.x), s2m(v.y)}; }