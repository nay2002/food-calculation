#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int soil_quality_index;
  char *pH;
  char *condition;
  char *organic_matter_content;
  char *cation_exchange_rate;
  char *soil_moisture;
  char *soil_drainage;
  char *soil_compaction;
  float total_yield_loss;
} soil_characterisitcs;

typedef struct {
  int approx_weight;
  float stage_losses;
  float early_stages;
  float seasonal_changes;
  float precautions;
} cultivation;

typedef struct {
  float initial_amount;
  float casual_loss;
  float precatuionary_loss;
  float amount_transported;
} transportation;

typedef struct {
  float storage_amount;
  float loss_storage;
  char *seasons;
  char demand;
  float reduced_loss;
  float final_amount;
} storage;

typedef struct {
  float acquired_amount;
  float wasteage;
  float effective_amount;
} commercial;

typedef struct {
  float amount_bought;
  float kitchen_loss;
  float amount_consumed;
  float reduction_loss;
} household;

// complete
char *dynamic_memory_allocation(int size) {
  char *buffer;
  buffer = (char *)malloc((size + 1) * sizeof(char));
  if (buffer == NULL) {
    printf("\nThe memory cannot be allocated for buffer.");
    exit(0);
  }
  return buffer;
}

// complete
int read_integer(int x, int lower, int upper) {
  int len = 0;
  int decimal_counter = 0;
  int valid = 0, invalid = 0;
  char *buffer;
  int buffer_size = 40;
  buffer = dynamic_memory_allocation(buffer_size);
  // input validation starts here
  enum Validation { NO_ERROR, INVALID_INPUT, INVALID_RANGE };
  const char *Validation_message[] = {
      " ",
      "\nInvalid Input. The provided input cannot be accepted because it is "
      "not in integer format, please ensure that there are no decimal points "
      "or characters present in the input.",
      "\nInvalid Range. The provided input cannot be accepted because it is "
      "out of the necessary range. Please refer to the input prompt to find "
      "the range."};
  int Validation = NO_ERROR;

  while (!valid) {
    // taking input by the user
    fgets(buffer, buffer_size, stdin);

    // removing wide spaces
    buffer[strcspn(buffer, "\r\n")] = 0;

    // checking negative sign
    int i = 0;
    if (buffer[i] == '-') {
      i = 1;
    }

    // looping throught the characters of string
    for (; i < strlen(buffer); i++) {
      // counting decimal points
      if (buffer[i] == '.') {
        decimal_counter++;
      }

      // checking for !is digit
      if ((!isdigit(buffer[i])) && (buffer[i] != '.')) {
        invalid = 1;
        break;
      }
    }

    // checking if there is any decimal point
    if (decimal_counter != 0) {
      invalid = 1;
      decimal_counter = 0;
    }

    // converting the string into the required data type
    else if ((sscanf(buffer, "%d%n", &x, &len) != 1) ||
             (len != strlen(buffer))) {
      invalid = 1;
    }

    // checking if the input is in correct range
    else if ((invalid == 0) && (x < lower || x > upper)) {
      printf("%-s", Validation_message[INVALID_RANGE]);
      continue;
    }

    else {
      valid = 1;
      invalid = 0;
      decimal_counter = 0;
    }

    if (invalid) {
      printf("%-s", Validation_message[INVALID_INPUT]);
      invalid = 0;
      decimal_counter = 0;
    } else {
      return x;
    }
  }
  free(buffer);
}

// complete
void data_intake(cultivation *c) {
  int weight;
  printf("Enter the estimated weight of cereal that you expect to harvest (0 - "
         "1000 tonnes):  ");
  weight = read_integer(weight, 0, 1001);
  float season = 0.075;
  float cultivate = 0.125;
  float prepared = 0.1;

  c->approx_weight = weight;
  c->seasonal_changes = season;
  c->early_stages = cultivate;
  c->precautions = prepared;
}

// complete   
void soil_evaluation(soil_characterisitcs *s) {  
  int quality;
  printf("Enter the soil quality index of the land (0 -100): ");
  quality = read_integer(quality, 0, 100);
  s->soil_quality_index = quality;
  if ((s->soil_quality_index <= 100) && (s->soil_quality_index >= 80)) {

    s->condition = dynamic_memory_allocation(strlen("Excellent") + 1);
    strcpy(s->condition, "Excellent");

    s->pH = dynamic_memory_allocation(strlen("6.0 to 7.0") + 1);
    strcpy(s->pH, "6.0 to 7.0");

    s->organic_matter_content =
        dynamic_memory_allocation(strlen("3% to 6%") + 1);
    strcpy(s->organic_matter_content, "3% to 6%");

    s->cation_exchange_rate =
        dynamic_memory_allocation(strlen("15 to 30 meq/100gm") + 1);
    strcpy(s->cation_exchange_rate, "15 to 30 meq/100gm");

    s->soil_moisture = dynamic_memory_allocation(strlen("50% to 70%") + 1);
    strcpy(s->soil_moisture, "50% to 70%");

    s->soil_drainage = dynamic_memory_allocation(
        strlen("Rating 2.7 - Excellent drainage.") + 1);
    strcpy(s->soil_drainage, "Rating 2.7 - Excellent drainage.");

    s->soil_compaction = dynamic_memory_allocation(
        strlen("Bulk density - 1.0 to 1.4 grams per cubic centimeter.") + 1);
    strcpy(s->soil_compaction,
           "Bulk density - 1.0 to 1.4 grams per cubic centimeter.");

    s->total_yield_loss = 0.03;
  }

  else if ((s->soil_quality_index <= 79) && (s->soil_quality_index >= 60)) {

    s->condition = dynamic_memory_allocation(strlen("Good") + 1);
    strcpy(s->condition, "Good");

    s->pH = dynamic_memory_allocation(strlen("6.0 to 7.5") + 1);
    strcpy(s->pH, "6.0 to 7.5");

    s->organic_matter_content =
        dynamic_memory_allocation(strlen("2% to 4%") + 1);
    strcpy(s->organic_matter_content, "2% to 4%");

    s->cation_exchange_rate =
        dynamic_memory_allocation(strlen("10 to 20 meq/100gm") + 1);
    strcpy(s->cation_exchange_rate, "10 to 20 meq/100gm");

    s->soil_moisture = dynamic_memory_allocation(strlen("50% to 70%") + 1);
    strcpy(s->soil_moisture, "50% to 70%");

    s->soil_drainage = dynamic_memory_allocation(
        strlen("Rating 2.4 - Excellent drainage.") + 1);
    strcpy(s->soil_drainage, "Rating 2.4 - Excellent drainage.");

    s->soil_compaction =
        dynamic_memory_allocation(strlen("Bulk density is approximately is 1.2 "
                                         "to 1.6 grams per cubic centimeter.") +
                                  1);
    strcpy(s->soil_compaction,
           "Bulk density - 1.2 to 1.6 grams per cubic centimeter.");

    s->total_yield_loss = 0.07;
  }

  else if ((s->soil_quality_index <= 59) && (s->soil_quality_index >= 40)) {

    s->condition = dynamic_memory_allocation(strlen("Fair") + 1);
    strcpy(s->condition, "Fair");

    s->pH = dynamic_memory_allocation(strlen("6.0 to 7.0") + 1);
    strcpy(s->pH, "6.0 to 7.0");

    s->organic_matter_content =
        dynamic_memory_allocation(strlen("1% to 2%") + 1);
    strcpy(s->organic_matter_content, "1% to 2%");

    s->cation_exchange_rate =
        dynamic_memory_allocation(strlen("5 to 10 meq/100gm") + 1);
    strcpy(s->cation_exchange_rate, "5 to 10 meq/100gm");

    s->soil_moisture = dynamic_memory_allocation(strlen("40% to 60%") + 1);
    strcpy(s->soil_moisture, "40% to 60%");

    s->soil_drainage =
        dynamic_memory_allocation(strlen("Rating 2 - Efficient drainage.") + 1);
    strcpy(s->soil_drainage, "Rating 2- Efficient drainage.");

    s->soil_compaction = dynamic_memory_allocation(
        strlen("Bulk density - 1.4 to 1.8 grams per cubic centimeter.") + 1);
    strcpy(s->soil_compaction,
           "Bulk density - 1.4 to 1.8 grams per cubic centimeter.");

    s->total_yield_loss = 0.16;
  }

  else if ((s->soil_quality_index <= 39) && (s->soil_quality_index >= 20)) {

    s->condition = dynamic_memory_allocation(strlen("Poor") + 1);
    strcpy(s->condition, "Poor");

    s->pH = dynamic_memory_allocation(strlen("5.0 to 6.5") + 1);
    strcpy(s->pH, "5.0 to 6.5");

    s->organic_matter_content =
        dynamic_memory_allocation(strlen("0.5% to 1%") + 1);
    strcpy(s->organic_matter_content, "0.5% to 1%");

    s->cation_exchange_rate =
        dynamic_memory_allocation(strlen("2 to 5 meq/100gm") + 1);
    strcpy(s->cation_exchange_rate, "2 to 5 meq/100gm");

    s->soil_moisture = dynamic_memory_allocation(strlen("30% to 50%") + 1);
    strcpy(s->soil_moisture, "30% to 50%");

    s->soil_drainage =
        dynamic_memory_allocation(strlen("Rating 1 - Poor drainage.") + 1);
    strcpy(s->soil_drainage, "Rating 1 - poor drainage.");

    s->soil_compaction = dynamic_memory_allocation(
        strlen("Bulk density - 1.6 to 2.0 grams per cubic centimeter.") + 1);
    strcpy(s->soil_compaction,
           "Bulk density - 1.6 to 2.0 grams per cubic centimeter.");

    s->total_yield_loss = 0.3;
  }

  else if ((s->soil_quality_index <= 19) && (s->soil_quality_index >= 0)) {

    s->condition = dynamic_memory_allocation(strlen("Very poor") + 1);
    strcpy(s->condition, "Very poor");

    s->pH = dynamic_memory_allocation(strlen("4.5 to 6.0") + 1);
    strcpy(s->pH, "4.5 to 6.0");

    s->organic_matter_content =
        dynamic_memory_allocation(strlen("0.1% to 0.5%") + 1);
    strcpy(s->organic_matter_content, "0.1% to 0.5%");

    s->cation_exchange_rate =
        dynamic_memory_allocation(strlen("1 to 3 meq/100gm") + 1);
    strcpy(s->cation_exchange_rate, "1 to 3 meq/100gm");

    s->soil_moisture = dynamic_memory_allocation(strlen("20% to 40%") + 1);
    strcpy(s->soil_moisture, "20% to 40%");

    s->soil_drainage =
        dynamic_memory_allocation(strlen("Rating 1 - Poor drainage.") + 1);
    strcpy(s->soil_drainage, "Rating 1 - Poor drainage.");

    s->soil_compaction = dynamic_memory_allocation(
        strlen("Bulk density - 1.8 to 2.5 grams per cubic centimeter.") + 1);
    strcpy(s->soil_compaction,
           "Bulk density - 1.8 to 2.5 grams per cubic centimeter.");

    s->total_yield_loss = 0.5;
  }
}

// complete
void precautions(soil_characterisitcs *s) {                 
  if (strcmp(s->condition, "Excellent") == 0) {
    printf("\n\n\033[1mThe necessary precautions that can be taken to reduce "
           "yield loss by 1 percent:\033[0m ");
    printf("\n\n•Regularly monitor pH levels.");
    printf("\n\n•Preserve CEC by maintaining orgnaic level and minimizing soil "
           "compaction.");
    printf("\n\n•Use machinery with low ground pressure.\n\n");
    s->total_yield_loss = 0.02;
  } else if (strcmp(s->condition, "Good") == 0) {
    printf("\n\n\033[1mThe necessary precautions that can be taken to reduce "
           "yield loss by 3.5 percent:\033[0m ");
    printf("\n\n•Adjust pH using appropriate amendmets.");
    printf("\n\n•Enchnace CEC by incorporating orgnaic matter and clay "
           "materials.");
    printf("\n\n•Use conversion tillage technique to retain organic matter.");
    printf("\n\n•Avoid Excessing machinery traffic on wet soil.");
    printf("\n\n•Maintain appropriate soil drainage through land shaping and "
           "contouring.\n\n");
    s->total_yield_loss = 0.035;
  } else if (strcmp(s->condition, "Fair") == 0) {
    printf("\n\n\033[1mThe necessary precautions that can be taken to reduce "
           "yield loss by 7 percent:\033[0m ");
    printf("\n\n•Adjust pH using appropriate amendmets.");
    printf("\n\n•Enchnace CEC by incorporating orgnaic matter and clay "
           "materials.");
    printf("\n\n•Avoid Excessing machinery traffic on wet soil.");
    printf("\n\n•Maintain appropriate soil drainage through land shaping and "
           "contouring.");
    printf("\n\n•Practice crop rotation to maximum nutrient availability.");
    printf("\n\n•Implement water conservation techniques such as drip "
           "irrigation to enhance soil moisture retention.\n\n");
    s->total_yield_loss = 0.09;
  } else if (strcmp(s->condition, "Poor") == 0) {
    printf("\n\n\033[1mThe necessary precautions that can be taken to reduce "
           "yield loss by 20 percent:\033[0m ");
    printf("\n\n•Adjust pH gradually by applying ammendments.");
    printf("\n\n•Perform thorough soil testing to idenity nutrients deficiency "
           "and imbalances.");
    printf("\n\n•Apply targeted fertilizers or organic ammendments based on "
           "soil test recommendations.");
    printf("\n\n•Increase organic matter through the addition of compost, "
           "cover crops, or manure.");
    printf("\n\n•Consider incorporating green manure or biochar to enhance "
           "organic matter content.");
    printf("\n\n•Focus on improving soil structure and organic matter content "
           "to enhance CEC.");
    printf("\n\n•Address drainage issues to prevent waterlogging or excessive "
           "dryness.\n\n");
    s->total_yield_loss = 0.1;
  } else if (strcmp(s->condition, "Very poor") == 0) {
    printf("\n\n\033[1mThe necessary precautions that can be taken to reduce "
           "yield loss by 40 percent: \033[0m");
    printf("\n\n•Implement a long-term plan to gradually adjust the pH by "
           "applying appropriate amendments based on soil test results.");
    printf("\n\n•Consider using acidifying or alkalizing materials in extreme "
           "cases, following recommended guidelines.");
    printf("\n\n•Apply targeted fertilizers or organic amendments based on "
           "soil test recommendations and crop requirements.");
    printf("\n\n•Implement practices to enhance nutrient cycling, such as "
           "cover cropping, composting, or incorporating organic matter.");
    printf("\n\n•Consider incorporating biochar or other soil amendments to "
           "boost organic matter content.");
    printf("\n\n•Minimize erosion through conservation practices to protect "
           "soil aggregates.");
    printf("\n\n•Install appropriate drainage systems to facilitate excess "
           "water removal.");
    printf("\n\n•Address severe soil compaction by implementing deep tillage "
           "or subsoiling techniques.");
    printf("\n\n• Minimize machinery traffic on wet soils and avoid heavy "
           "equipment during critical periods.\n\n");
    s->total_yield_loss = 0.1;
  }
}

// complete
void soil_report(soil_characterisitcs *s) {
  printf("\n\n\n\033[1mThe Soil Report is as follows: \033[0m");
  printf("\n\n•Soil Quality Index: \033[1m %-d \033[0m", s->soil_quality_index); 
  printf("\n\n•The quality of the soil is \033[1m %-s \033[0m", s->condition);
  printf("\n\n•pH value: \033[1m %-s\033[0m", s->pH);
  printf("\n\n•Organic Matter content: \033[1m %-s\033[0m",
         s->organic_matter_content);
  printf("\n\n•Cation Exchange Capaity: \033[1m %-s\033[0m",
         s->cation_exchange_rate);
  printf("\n\n•Soil Moisture: \033[1m %-s\033[0m", s->soil_moisture);
  printf("\n\n•Soil Drainage: \033[1m %-s\033[0m", s->soil_drainage);
  printf("\n\n•Soil Compaction:\033[1m %-s\033[0m", s->soil_compaction);
  printf("\n\n•A total yield of \033[1m%-.3f \033[0m percent is precedented if "
         "necessary precautions are not taken.\n\n",
         s->total_yield_loss * 100);
}

// complete to
void loss_calculations(cultivation *c, soil_characterisitcs *s) {
  printf("\n\n\033[1m Food loss during the cultivation period: \033[0m");
  printf("\n\n•The loss of crops due to bad conditions of soil is : "
         "\033[1m%-.3f tonnes\033[0m",
         c->approx_weight * s->total_yield_loss);
  c->stage_losses = c->approx_weight - (c->approx_weight * s->total_yield_loss);
  printf("\n•The yield loss during cultivation is 12.5 percent, which "
         "evaluates to : \033[1m%-.3f tonnes \033[0m",
         c->stage_losses * c->early_stages);
  printf("\n•The yeild loss due to seasonal changes is 7.5 percent, which "
         "evaluates to: \033[1m%-.3f tonnes \033[0m",
         c->stage_losses * c->seasonal_changes);
  printf("\n•When all the precautions are in place only 10 percent yield loss "
         "occurs, which evaluates to : \033[1m%-.3f tonnes \033[0m",
         c->stage_losses * c->precautions);
  c->stage_losses = c->stage_losses - (c->stage_losses * c->precautions);
  printf("\n•Total amount of health grains harvested after taking the "
         "necessary precautions is : \033[1m%-.3f tonnes \033[0m ",
         c->stage_losses);

  printf("\n\n\033[1m Precautionary measures to be taken for cultivation : "
         "\033[0m");
  printf("\n\n•Use biological controls, cultural practices, and targeted "
         "pesticides to manage pests and diseases, reducing reliance on "
         "chemicals and promoting ecological balance.");
  printf("\n\n•Add organic matter, use conservation tillage, and implement "
         "cover cropping to improve soil health and crop resilience to climate "
         "changes.");
  printf("\n\n•Choose crops bred to withstand regional climate challenges, "
         "like drought or heat tolerance, for improved resilience.\n\n");
}

// complete
void transport_roadmap(transportation *t, cultivation *c) {
  t->initial_amount = c->stage_losses;
  t->casual_loss = 0.10;
  t->precatuionary_loss = 0.07;
  printf("\n\n\033[1m Food loss during the transportation period: \033[0m");
  printf(
      "\n\n•The food loss during transportation without precautionary measures "
      "is 10 percent, which evaluates to : \033[1m%-.3f tonnes \033[0m ",
      t->initial_amount * t->casual_loss);
  printf(
      "\n•The food loss during transportation with all precautionary measures "
      "in place is 7 percent, which evaluates to : \033[1m%-.3f tonnes \033[0m",
      t->initial_amount * t->precatuionary_loss);
  t->amount_transported =
      t->initial_amount - (t->initial_amount * t->precatuionary_loss);
  printf("\n•Amount of crops that arrive at the storage facility without "
         "damage or loss : \033[1m%-.3f tonnes \033[0m",
         t->amount_transported);

  printf("\n\n\033[1m Precautionary measures to be taken for transportation : "
         "\033[0m");
  printf("\n\n•Handle products with care and avoid excessive shaking or impact "
         "during transportation.");
  printf("\n\n•Monitor and control temperature conditions to prevent spoilage "
         "and maintain product quality.");
  printf("\n\n•Store products in suitable conditions, such as proper "
         "ventilation and protection from sunlight or extreme temperatures.");
  printf("\n\n•Maintain cleanliness, adhere to food safety standards, and "
         "prevent contamination during transportation.");
}

void storage_loss(storage *r, transportation *t) {   //Come herererererere came 
  r->storage_amount = t->amount_transported;
  char *name;
  int name_size = 40;
  name = dynamic_memory_allocation(name_size);
  printf("\n\n\nEnter the season (summer,winter,monsoon): ");
  fgets(name, name_size, stdin);
  name[strcspn(name, "\r\n")] = 0;
  r->seasons = dynamic_memory_allocation(strlen(name) + 1);
  strcpy(r->seasons, name);
  free(name);
  printf("\nIs the crop under consideration in demand? (y/n) : ");
  scanf(" %c", &r->demand);
  if (strcmp(r->seasons, "summer") == 0) {
    if (r->demand == 'y') {
      r->loss_storage = 0.18;
      printf("\n\n\033[1mFor Summer Season: \033[0m");
      printf("\n\n\nFood loss of 18 percent takes place without precautionary "
             "measures, which evaluates to: \033[1m%-.3f tonnes \033[0m",
             r->storage_amount * r->loss_storage);
      r->reduced_loss = 0.075;
      printf("\nFood loss can be reduced to 7.5 percent when precationary "
             "measures are in place, which evaluates to : \033[1m%-.3f tonnes "
             "\033[0m",
             r->storage_amount * r->reduced_loss);
      r->final_amount = r->storage_amount - r->reduced_loss * r->storage_amount;
      printf("\nThe weight of food that is not spoiled or damaged during "
             "storage: \033[1m%-.3f tonnes \033[0m",
             r->final_amount);
    } else {
      r->loss_storage = 0.15;
      printf("\n\n\033[1mFor Summer Season: \033[0m");
      printf("\n\n\nFood loss of 15 percent takes place without precautionary "
             "measures, which evaluates to: \033[1m%-.3f tonnes \033[0m",
             r->storage_amount * r->loss_storage);
      r->reduced_loss = 0.09;
      printf(
          "\nFood loss can be reduced to 9 percent when preacutionary measures "
          "are in place, which evaluates to: \033[1m%-.3f tonnes \033[0m",
          r->storage_amount * r->reduced_loss);
      r->final_amount = r->storage_amount - r->reduced_loss * r->storage_amount;
      printf("\nThe weight of food that is not spoiled or damaged during "
             "storage: \033[1m%-.3f tonnes \033[0m",
             r->final_amount);
    }

    printf("\n\n\033[1m Precautionary measures for Summer: \033[0m");
    printf("\n\n•Shield storage areas from direct sunlight to prevent "
           "excessive heat buildup and temperature fluctuations");
    printf(
        "\n\n•Implement a strict cleaning schedule to remove any spilled or "
        "decaying produce that can attract pests and contribute to spoilage");
    printf("\n\n•Implement a first-in, first-out (FIFO) system to ensure that "
           "older crops are used or sold first.");
  } else if (strcmp(r->seasons, "winter") == 0) {
    if (r->demand == 'y') {
      r->loss_storage = 0.4;
      printf("\n\n\033[1mFor Winter Season: \033[0m");
      printf("\n\n\nFood loss of 40 percent takes place without precautionary "
             "measures, which evaluates to: \033[1m%-.3f tonnes \033[0m",
             r->storage_amount * r->loss_storage);
      r->reduced_loss = 0.14;
      printf(
          "\nFood loss can be reduced to 14 percent with precautionary "
          "measures in place, which evaluates to: \033[1m%-.3f tonnes \033[0m",
          r->storage_amount * r->reduced_loss);
      r->final_amount = r->storage_amount - r->reduced_loss * r->storage_amount;
      printf("\nThe weight of food that is not spoiled or damaged during "
             "storage: \033[1m%-.3f tonned \033[0m",
             r->final_amount);
    } else {
      r->loss_storage = 0.25;
      printf("\n\n\033[1mFor Winter Season: \033[0m");
      printf("\n\n\nFood loss of 25 percent takes place without precautionary "
             "measures, which evaluates to: \033[1m%-.3f tones \033[0m",
             r->storage_amount * r->loss_storage);
      r->reduced_loss = 0.06;
      printf("\nFood loss can reduced to 6 percent with precautionary measures "
             "in place, which evaluates to: \033[1m%-.3f tonnes \033[0m",
             r->storage_amount * r->reduced_loss);
      r->final_amount = r->storage_amount - r->reduced_loss * r->storage_amount;
      printf("\nThe weight of food that is not spoiled or damaged during "
             "storage: \033[1m%-.3f tonnes \033[0m",
             r->final_amount);
    }

    printf("\n\n\033[1m Precautionary measures for Winter: \033[0m");
    printf("\n\n•Poor insulation in winter risks freezing crops, leading to "
           "potential damage and loss.");
    printf("\n\n•Implement proper stacking and organizing techniques to allow "
           "for proper air circulation and reduce the risk of condensation");
    printf("\n\n•Use moisture control methods like desiccants to minimize "
           "excess humidity and prevent spoilage and mold in stored crops.");
  } else if (strcmp(r->seasons, "monsoon") == 0) {
    if (r->demand == 'y') {
      r->loss_storage = 0.1635;
      printf("\n\n\033[1mFor Monsoon Season: \033[0m");
      printf(
          "\n\n\nFood loss of 16.35 percent takes place without precautionary "
          "measures, which evaluates to: \033[1m%-.3f tonnes \033[0m",
          r->storage_amount * r->loss_storage);
      r->reduced_loss = 0.134;
      printf(
          "\nFood loss can be reduced to 13.4 percent with precautionary "
          "measures in place, which evaluates to: \033[1m%-.3f tonnes \033[0m",
          r->storage_amount * r->reduced_loss);
      r->final_amount = r->storage_amount - r->reduced_loss * r->storage_amount;
      printf("\nThe weight of food that is not spoiled or damaged during "
             "storage: \033[1m%-.3f tonnes \033[0m \n\n",
             r->final_amount);
    } else {
      r->loss_storage = 0.1635;
      printf("\n\n\033[1mFor Monsoon Season: \033[0m");
      printf(
          "\n\n\nFood loss of 16.35 percent takes place without precautionary "
          "measures, which evaluates to: \033[1m%-.3f tonnes \033[0m",
          r->storage_amount * r->loss_storage);
      r->reduced_loss = 0.134;
      printf(
          "\nFood loss can be cut down to 13.4 percent with precautionary "
          "measures in place, which evaluates to: \033[1m%-.3f tonnes \033[0m",
          r->storage_amount * r->reduced_loss);
      r->final_amount = r->storage_amount - r->storage_amount * r->reduced_loss;
      printf("\nThe weight of food that is not spoiled or damaged during "
             "storage: \033[1m%-.3f tonnes \033[0m\n\n",
             r->final_amount);
    }

    printf("\n\n\033[1m Precautionary measures for Monsoon: \033[0m");
    printf("\n\n•The storage area should be cool, dry, and well-ventilated");
    printf("\n\n•The crops should be inspected regularly for signs of "
           "spoilage, such as mold or discoloration.");
    printf("\n\n•The crops should be rotated regularly so that the oldest "
           "items are used first.");
  } else {
  }
  free(r->seasons);
}

void commercial_wasteage(commercial *l, storage *r) {            //Love u Team :)
  l->acquired_amount = r->final_amount;
  l->wasteage = 0.175;
  l->effective_amount = l->acquired_amount - l->wasteage * l->acquired_amount;
  printf("\n\n\n\033[1m Food service Establishment food losses: \033[0m");
  printf("\n\n•The food loss that occurs in food establishments is nearly 17 "
         "percent, which evaluates to: \033[1m%-.3f tonnes \033[0m",
         l->acquired_amount * l->wasteage);
  printf("\n\n•The effective amount of food that is consumed is: \033[1m%-.3f "
         "tonnes \033[0m \n",
         l->effective_amount);
  printf("\n•Precautionary measures can be taken to further refine the "
         "handling of food in these kitchens but the scope of decreasing the "
         "wasteage is negligible. \n");
  printf("\n\n\033[1m Precautionary measures for Food Establishments: \033[0m");
  printf("\n\n•Menu planning and portion control to avoid overproduction and "
         "plate waste.");
  printf(
      "\n\n•Donating surplus food and repurposing leftovers to reduce waste.");
  printf("\n\n•Monitoring and analyzing data to identify patterns and improve "
         "waste reduction strategies.");
}

void household_loss(household *h, storage *r) {
  h->amount_bought = r->final_amount;
  h->kitchen_loss = 0.11;
  h->reduction_loss = 0.0825;
  h->amount_consumed =
      h->amount_bought - (h->reduction_loss * h->amount_bought);
  printf("\n\n\n\033[1m Domestic household food losses : \033[0m");
  printf("\n\n•The food loss that occurs in domestic households is nearly 11 "
         "percent , which evaluates to: \033[1m %-.3f tonnes \033[0m",
         h->amount_bought * h->kitchen_loss);
  printf("\nFood loss can be reduced to 8.25 percent with precautionary "
         "measures in place, which evaluates to: \033[1m%-.3f tonnes \033[0m",
         h->amount_bought * h->reduction_loss);
  printf("\nThe effective amount of food that is consumed is: \033[1m %-.3f "
         "tonnes  \033[0m",
         h->amount_consumed);
  printf(
      "\n\n\033[1m Precautionary measures for Domestic households : \033[0m");
  printf("\n\n•Store perishable foods in the refrigerator at the right "
         "temperatures and use airtight containers to maintain freshness.");
  printf("\n\n•Use the first in first out method to ensure older food items "
         "are consumed before newer ones, reducing the chances of expiration "
         "and spoilage.");
  printf("\n\n•Plan meals in advance to avoid overbuying or cooking excessive "
         "amounts of food, and serve appropriate portions to minimize "
         "leftovers and food waste.");
}

int main(void) {
  int choice;
  printf("Please enter the situation for which you are calculating ( 1 - Food "
         "Service establishments, 0 - Dosmestic households): ");
  choice = read_integer(choice, 0, 1);
  soil_characterisitcs land;
  cultivation crops;
  transportation route;
  storage warehouse;
  commercial business;
  household home;
  data_intake(&crops);
  soil_evaluation(&land);
  soil_report(&land);
  precautions(&land);
  loss_calculations(&crops, &land);
  transport_roadmap(&route, &crops);
  storage_loss(&warehouse, &route);

  switch (choice) {
  case 0:
    household_loss(&home, &warehouse);
    break;
  case 1:
    commercial_wasteage(&business, &warehouse);
    break;
  }
  return 0;
}
