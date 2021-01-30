#include "main.h"

BSDATA(spelli) = {
	{"Guidance", 0, Divination},
	{"Light", 0, Evocation},
	{"Resistance", 0, Abjuration},
	{"SacredFlame", 0, Evocation, StandartAction, Range60, {Verbal, Somatic}, Instantaneous, {Radiant, 1, 8}},
	{"SpareTheDying", 0, Necromancy},
	{"Thaumaturgy", 0, Transmutation},
	{"AcidSplash", 0, Conjuration},
	{"DancingLights", 0, Evocation},
	{"FireBolt", 0, Evocation},
	{"MageHand", 0, Conjuration},
	{"MinorIllusion", 0, Illusion},
	{"PoisonSpray", 0, Conjuration},
	{"Prestidigitation", 0},
	{"RayOfFrost", 0, Evocation, StandartAction, Range60, {Verbal, Somatic, NeedAttack, ExtraDice}, Instantaneous, {Cold, 1, 8}},
	{"ShockingGrasp", 0, Evocation, StandartAction, Touch, {Verbal, Somatic, NeedAttack, ExtraDice}, Instantaneous, {Lightning, 1, 8}},
	{"Bless", 1, Enchantment, StandartAction, Range30, {Verbal, Somatic, Material, ExtraCreature}, Concentration},
	{"Command", 1, Enchantment, StandartAction, Range60, {Verbal, ExtraCreature}, DurationRound},
	{"CureWounds", 1, Evocation, StandartAction, Touch, {Verbal, Somatic, ExtraDice}, Instantaneous, {Radiant, 1, 8}},
	{"DetectMagic", 1, Divination, StandartAction, Self, {Verbal, Somatic, Ritual}, Concentration},
	{"GuidingBolt", 1, Evocation, StandartAction, Range120, {Verbal, Somatic}, DurationRound, {Radiant, 4, 6}},
	{"HealingWord", 1, Evocation, BonusAction, Range60, {Verbal}, Instantaneous, {Radiant, 1, 4, 1}},
	{"InflictWounds", 1, Necromancy, StandartAction, Touch, {Verbal, Somatic, NeedAttack}, Instantaneous, {Necrotic, 3, 6}},
	{"Sanctuary", 1, Abjuration, BonusAction, Range30, {Verbal, Somatic, Material}, DurationMinute},
	{"ShieldOfFaith", 1, Abjuration, BonusAction, Range60, {Verbal, Somatic, Material}, Concentration},
};
assert_enum(spelli, ShieldOfFaith)