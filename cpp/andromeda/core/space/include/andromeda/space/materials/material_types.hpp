#pragma once


namespace andromeda::space
{
    /// @brief Enumerates the built-in material presets supported by the engine.
    enum class MaterialType
    {
        None,

        Emerald,
        Jade,
        Obsidian,
        Pearl,
        Ruby,
        Turquoise,
        Brass,
        Bronze,
        Chrome,
        Copper,
        Gold,
        Silver,
        BlackPlastic,
        CyanPlastic,
        GreenPlastic,
        RedPlastic,
        WhitePlastic,
        YellowPlastic,
        BlackRubber,
        CyanRubber,
        GreenRubber,
        RedRubber,
        WhiteRubber,
        YellowRubber,

        Mercury,
        Venus,
        Earth,
        Mars,
        Jupiter,
        Saturn,
        Uranus,
        Neptune,

        Moon,
        Phobos,
        Deimos,
        Io,
        Europa,
        Ganymede,
        Callisto,
        Titan,
        Enceladus,
        Rhea,
        Iapetus,
        Miranda,
        Ariel,
        Umbriel,
        Titania,
        Oberon,
        Triton,
        Nereid,
        Proteus,

        Count  // always keep last; useful for iteration/arrays
    };
}
