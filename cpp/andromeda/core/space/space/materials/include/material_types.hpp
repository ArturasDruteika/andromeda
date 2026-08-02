#ifndef SPACE__MATERIAL_TYPES__HPP
#define SPACE__MATERIAL_TYPES__HPP


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

        Count  // always keep last; useful for iteration/arrays
    };
}


#endif // SPACE__MATERIAL_TYPES__HPP