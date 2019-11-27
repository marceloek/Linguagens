<template>
  <div class="card mt-4 mb-4">
    <div class="card-body">
      <h3>{{ title }}</h3>
      <ul class="list-group">
        <li
          v-for="(alt, index) in alternatives"
          v-bind:key="index"
          :class="`list-group-item ${btnClass(index)}`"
          v-on:click="chooseAlternative(index)"
        >{{ alt.text }}
          <!-- <button
            :class="`btn ${btnClass(index)}`"
            v-on:click="chooseAlternative(index)"
          >{{ alt.text }}</button> -->
        </li>
      </ul>
      <button
        class="btn btn-outline-secondary mt-4"
        :disabled="!choiceMade"
        v-on:click="complete()"
      >Próxima Pergunta</button>
    </div>
  </div>
</template>

<script>
export default {
  name: "Question",
  data: function() {
    return {
      choiceMade: false,
      correctAnswer: false,
      answer: 0
    };
  },
  props: {
    title: String,
    alternatives: Array, // [{text: String, correct: Bool}]
    onComplete: Function
  },
  methods: {
    chooseAlternative: function(index) {
      if (this.choiceMade) return;
      this.correctAnswer = this.alternatives[index].correct;
      this.choiceMade = true;
      this.answer = index;
    },
    btnClass: function(index) {
      if (this.choiceMade && this.alternatives[index].correct) {
        return "list-group-item-success";
      } else if (this.choiceMade && this.answer === index) {
        return "list-group-item-danger";
      } else if (this.choiceMade) {
        return "list-group-item-link";
      } else {
        return "list-group-item-outline-primary";
      }
    },
    complete: function() {
      if (!this.choiceMade) return;
      this.onComplete(this.correctAnswer);
    }
  }
};
</script>

<style scoped>
.list-group-item {
  cursor: pointer;
}
.list-group-item:hover:not(.list-group-item-success):not(.list-group-item-danger) {
    background-color: #f5f5f5;
}
</style>